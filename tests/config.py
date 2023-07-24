import re
import os
import argparse
from typing import Final, Callable
from pathlib import Path
from sdf_pipeline.pubchem import get_id as _get_pubchem_id


def get_molfile_id(sdf_path: Path) -> Callable:
    if "mcule" in sdf_path.stem:
        return _get_mcule_id
    elif "inchi" in sdf_path.stem:
        return _get_inchi_id
    return _get_pubchem_id


def _get_inchi_id(molfile: str) -> str:
    molfile_id = molfile.splitlines()[-2].strip()

    return molfile_id


def _get_mcule_id(molfile: str) -> str:
    molfile_id_pattern = re.compile(r"<Mcule_ID>(.*?)>", re.DOTALL)
    molfile_id_match = molfile_id_pattern.search(molfile)
    molfile_id = molfile_id_match.group(1).strip() if molfile_id_match else ""

    return molfile_id


def get_dataset_arg() -> str:
    parser = argparse.ArgumentParser(
        description="Choose a dataset {ci, pubchem}",
    )
    parser.add_argument(
        "dataset",
        choices=["ci", "pubchem"],
        type=str,
        nargs=1,
        help="Choose a dataset from {ci, pubchem}",
    )
    (dataset,) = parser.parse_args().dataset

    return dataset


TEST_PATH: Final[Path] = Path(__file__).parent.absolute()
INCHI_LIB_PATH: Final[Path] = TEST_PATH.joinpath("libinchi.so.dev")
INCHI_REFERENCE_LIB_PATH: Final[Path] = TEST_PATH.joinpath("libinchi.so.1.06.00")
N_PROCESSES: Final[int] = len(
    os.sched_getaffinity(0)
)  # https://docs.python.org/3/library/multiprocessing.html#multiprocessing.cpu_count

DATASETS: Final[dict] = {
    "ci": {
        "sdf_paths": TEST_PATH.joinpath("data/ci").glob("*.sdf.gz"),
        "log_path": TEST_PATH.joinpath("data/ci/"),
    },
    "pubchem": {
        "sdf_paths": TEST_PATH.joinpath("data/pubchem").glob("*.sdf.gz"),
        "log_path": TEST_PATH.joinpath("data/pubchem/"),
    },
}
