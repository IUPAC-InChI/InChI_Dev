import re
from typing import Final

INCHI_LIB_PATH: Final = "libinchi.so.dev"
INCHI_REFERENCE_LIB_PATH: Final = "libinchi.so.1.06.00"

MCULE_SDF_PATH: Final = "data/mcule.sdf.gz"
INCHI_SDF_PATH: Final = "data/inchi.sdf.gz"


def get_inchi_id(molfile: str) -> str:
    molfile_id = molfile.splitlines()[-2].strip()

    return molfile_id


def get_mcule_id(molfile: str) -> str:
    molfile_id_pattern = re.compile(r"<Mcule_ID>(.*?)>", re.DOTALL)
    molfile_id_match = molfile_id_pattern.search(molfile)
    molfile_id = molfile_id_match.group(1).strip() if molfile_id_match else ""

    return molfile_id
