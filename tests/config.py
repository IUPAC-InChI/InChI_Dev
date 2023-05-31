import re
from typing import Final

INCHI_LIB_PATH: Final[str] = "libinchi.so.dev"
INCHI_REFERENCE_LIB_PATH: Final[str] = "libinchi.so.1.06.00"


def get_inchi_id(molfile: str) -> str:
    molfile_id = molfile.splitlines()[-2].strip()

    return molfile_id


def get_mcule_id(molfile: str) -> str:
    molfile_id_pattern = re.compile(r"<Mcule_ID>(.*?)>", re.DOTALL)
    molfile_id_match = molfile_id_pattern.search(molfile)
    molfile_id = molfile_id_match.group(1).strip() if molfile_id_match else ""

    return molfile_id


DATASETS: Final[dict] = {
    "mcule": {
        "sdf_path": "data/mcule.sdf.gz",
        "molfile_id": get_mcule_id,
    },
    "inchi": {
        "sdf_path": "data/inchi.sdf.gz",
        "molfile_id": get_inchi_id,
    },
}
