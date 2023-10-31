import json
from pathlib import Path
from difflib import SequenceMatcher
from typing import Generator
from sdf_pipeline.core import read_records_from_gzipped_sdf
from .config import get_molfile_id, get_dataset_arg, DATASETS


def select_molfiles_from_sdf(
    sdf_path: Path, molfile_ids: set[str]
) -> Generator[tuple[str, str], None, None]:
    _get_molfile_id = get_molfile_id(sdf_path)

    for molfile in read_records_from_gzipped_sdf(sdf_path):
        molfile_id = _get_molfile_id(molfile)
        if molfile_id in molfile_ids:
            yield molfile_id, molfile

    return None


def get_html_diff(current: str, reference: str) -> str:
    html_diff: str = ""
    seq_matcher = SequenceMatcher(None, current, reference)

    for opcode, cur_beg, cur_end, ref_beg, ref_end in seq_matcher.get_opcodes():
        # returns a sequence of instructions for how to convert current into reference
        match opcode:
            case "equal":
                html_diff += current[cur_beg:cur_end]
            case "insert":
                html_diff += f"<ins style='background-color: #d4fcbc;'>{reference[ref_beg:ref_end]}</ins>"
            case "delete":
                html_diff += f"<del style='background-color: #fbb;'>{current[cur_beg:cur_end]}</del>"
            case "replace":
                html_diff += f"<del style='background-color: #fbb;'>{current[cur_beg:cur_end]}</del>"
                html_diff += f"<ins style='background-color: #d4fcbc;'>{reference[ref_beg:ref_end]}</ins>"
            case _:
                raise RuntimeError("Unknown opcode.")

    return html_diff


def write_html_log(sdf_log: dict, sdf_path: Path) -> None:
    with sdf_path.with_suffix(".html").open("w") as html_file:
        html_file.write("<!DOCTYPE html>\n")
        html_file.write("<html>\n")
        html_file.write("<head>\n")
        html_file.write(
            f"<title>InChI Regression Test Failures {sdf_path.name}</title>\n"
        )
        html_file.write("</head>\n")
        html_file.write("<body>\n")

        molfile_ids = set(sdf_log.keys())
        for molfile_id, molfile in select_molfiles_from_sdf(sdf_path, molfile_ids):
            molfile_log: dict = sdf_log[molfile_id]
            html_file.write(f"<h1>{molfile_id}</h1>\n")

            html_file.write("<details>\n")
            html_file.write("<summary>metadata</summary>\n")
            html_file.write(f"<p>time: {molfile_log['time']}\n")
            html_file.write(
                f"<p>arguments to MakeINCHIFromMolfileText: {molfile_log['parameters']}\n"
            )
            html_file.write("</details>\n")

            html_file.write("<details>\n")
            html_file.write("<summary>SDF</summary>\n")
            html_file.write(
                f"<pre style='display: inline-block; border: 1px solid black; border-radius: 10px; padding: 10px'>{molfile}</pre>\n"
            )
            html_file.write("</details>\n")

            current: dict = molfile_log["current"]
            reference: dict = molfile_log["reference"]
            for key, current_value in current.items():
                reference_value = reference[key]
                html_file.write(f"<h3>{key}</h3>\n")
                html_file.write("<table>\n")
                html_file.write("<tr>\n")
                html_file.write("<td>current:</td>\n")
                html_file.write(f"<td>{current_value}</td>\n")
                html_file.write("</tr>\n")
                html_file.write("<td>reference:</td>\n")
                html_file.write(f"<td>{reference_value}</td>\n")
                html_file.write("<tr>\n")
                html_file.write("<td>difference:</td>\n")
                html_file.write(
                    f"<td>{get_html_diff(str(current_value), str(reference_value))}<td>\n"
                )
                html_file.write("</tr>\n")
                html_file.write("<table>\n")

        html_file.write("</body>\n")
        html_file.write("</html>\n")

    return None


if __name__ == "__main__":
    dataset = get_dataset_arg()

    log_paths = sorted(DATASETS[dataset]["log_path"].glob("*_regression_test.log"))
    if not log_paths:
        raise RuntimeError(
            f"There aren't any log file in {DATASETS[dataset]['log_path']}"
        )
    log_path: Path = log_paths[-1]  # process most recent log file; TODO: parametrize?
    previous_sdf: str = ""
    sdf_log: dict = {}

    with log_path.open("r") as log_file:
        for line in log_file:
            if not line.startswith("INFO:sdf_pipeline:regression test failed:"):
                continue
            log_entry = json.loads(
                line.lstrip("INFO:sdf_pipeline:regression test failed:")
            )

            if previous_sdf:
                if previous_sdf != log_entry["sdf"]:
                    write_html_log(
                        sdf_log,
                        DATASETS[dataset]["log_path"].joinpath(previous_sdf),
                    )
                    sdf_log = {}
            previous_sdf = log_entry["sdf"]

            info = json.loads(log_entry["info"])
            diff = json.loads(log_entry["diff"])
            current = json.loads(diff["current"])
            reference = json.loads(diff["reference"])

            molfile_log: dict = {}
            molfile_log["time"] = log_entry["time"]
            molfile_log["parameters"] = info["parameters"]
            molfile_log["current"] = {}
            molfile_log["reference"] = {}

            for key, current_value in current.items():
                reference_value = reference[key]
                if current_value != reference_value:
                    molfile_log["current"][key] = current_value
                    molfile_log["reference"][key] = reference_value

            sdf_log[log_entry["molfile_id"]] = molfile_log

        # take care of last or only SDF
        write_html_log(
            sdf_log,
            DATASETS[dataset]["log_path"].joinpath(previous_sdf),
        )
