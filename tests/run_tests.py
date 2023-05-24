from typing import Final, Callable
from inchi_api import make_inchi_from_molfile_text
from sdf_pipeline import drivers, utils

SDF_PATH: Final = "data/inchi.sdf.gz"


def _regression_consumer(
    molfile: str, get_molfile_id: Callable
) -> utils.ConsumerResult:
    _, inchi_string, _, _, _ = make_inchi_from_molfile_text(molfile, "-SNon -DoNotAddH")

    return utils.ConsumerResult(
        "regression ",
        utils.get_current_time(),
        get_molfile_id(molfile),
        inchi_string,
    )


def _get_molfile_id(molfile: str) -> str:
    molfile_id = molfile.splitlines()[-2].strip()

    return molfile_id


if __name__ == "__main__":
    args = drivers.parse_cli_args()

    if args.test_type == "regression":
        if args.compute_reference_result:
            drivers.regression_reference(
                sdf_path=SDF_PATH,
                log_path=args.result_destination,
                consumer_function=_regression_consumer,
                get_molfile_id=_get_molfile_id,
            )
        else:
            drivers.regression(
                sdf_path=SDF_PATH,
                log_path=args.result_destination,
                reference_path=args.reference_result,
                consumer_function=_regression_consumer,
                get_molfile_id=_get_molfile_id,
            )
