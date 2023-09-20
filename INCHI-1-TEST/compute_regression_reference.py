import ctypes
import subprocess
from functools import partial
from typing import Final
from sdf_pipeline import drivers
from .consumers import regression_consumer
from .config import (
    INCHI_REFERENCE_LIB_PATH,
    DATASETS,
    TEST_PATH,
    N_PROCESSES,
    get_molfile_id,
    get_dataset_arg,
    get_progress,
    get_current_time,
)


if __name__ == "__main__":
    dataset = get_dataset_arg()

    subprocess.run(
        f"{TEST_PATH}/download_inchi_regression_reference_lib.sh", check=True
    )

    INCHI_LIB: Final = ctypes.CDLL(str(INCHI_REFERENCE_LIB_PATH))
    exit_code = 0
    sdf_paths = list(DATASETS[dataset]["sdf_paths"])
    n_sdf = len(sdf_paths)
    print(
        f"\n{get_current_time()}: Starting to process {n_sdf} SDFs on {N_PROCESSES} cores.\n"
    )
    for i, sdf_path in enumerate(sdf_paths):
        log_path = DATASETS[dataset]["log_path"].joinpath(
            f"{sdf_path.stem}.regression_reference.sqlite"
        )
        if log_path.exists():
            print(
                f"{get_progress(i, n_sdf)}; Not re-computing reference for {sdf_path.name}."
            )
            continue
        exit_code = max(
            exit_code,
            drivers.regression_reference(
                sdf_path=sdf_path,
                log_path=log_path,
                consumer_function=partial(regression_consumer, inchi_lib=INCHI_LIB),
                get_molfile_id=get_molfile_id(sdf_path),
                number_of_consumer_processes=N_PROCESSES,
            ),
        )
        print(f"{get_progress(i + 1, n_sdf)}; Computed reference for {sdf_path.name}.")

    raise SystemExit(exit_code)
