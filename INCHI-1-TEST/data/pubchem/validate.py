import hashlib
from ...config import get_dataset_arg, DATASETS


if __name__ == "__main__":
    dataset = get_dataset_arg()
    sdf_paths = list(DATASETS[dataset]["sdf_paths"])
    
    for sdf_path in sdf_paths:
        with open(sdf_path.with_suffix(".gz"), "rb") as sdf_file:
            local_hash = hashlib.file_digest(sdf_file, "md5").hexdigest()
            try:
                with open(sdf_path.with_suffix(".gz.md5"), "r") as md5_file:
                    server_hash = md5_file.read().split()[0].strip()
                    if local_hash != server_hash:
                        print(f"{sdf_path.name}: local hash {local_hash} does not match server hash {server_hash}.")
            except FileNotFoundError as e:
                print(e)
            