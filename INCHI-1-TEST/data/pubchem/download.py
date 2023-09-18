from sdf_pipeline import pubchem
from sdf_pipeline.utils import get_current_time
from pathlib import Path


if __name__ == "__main__":
    for sdf_path in pubchem.download_all_sdf(
        destination_directory=Path(__file__).parent.absolute()
    ):
        print(f"{get_current_time()}: Downloaded {sdf_path}")
