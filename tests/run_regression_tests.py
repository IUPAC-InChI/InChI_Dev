import ctypes
import subprocess
from functools import partial
from typing import Final
from sdf_pipeline import drivers
from tests.consumers import regression_consumer
from tests.config import (
    INCHI_LIB_PATH,
    DATASETS,
    TEST_PATH,
    N_PROCESSES,
    get_molfile_id,
    get_dataset_arg,
)


if __name__ == "__main__":
    dataset = get_dataset_arg()

    subprocess.run(f"{TEST_PATH}/compile_inchi_lib.sh", check=True)

    INCHI_LIB: Final = ctypes.CDLL(str(INCHI_LIB_PATH))
    exit_code = 0

    for sdf_path in DATASETS[dataset]["sdf_paths"]:
        exit_code = max(
            exit_code,
            drivers.regression(
                sdf_path=sdf_path,
                log_path=DATASETS[dataset]["log_path"].joinpath(
                    f"{sdf_path.stem}.regression.sqlite"
                ),
                reference_path=DATASETS[dataset]["log_path"].joinpath(
                    f"{sdf_path.stem}.regression_reference.sqlite"
                ),
                consumer_function=partial(regression_consumer, inchi_lib=INCHI_LIB),
                get_molfile_id=get_molfile_id(sdf_path),
                number_of_consumer_processes=N_PROCESSES,
            ),
        )

    raise SystemExit(exit_code)
