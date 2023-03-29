import pytest
import gzip
from inchi_api import make_inchi_from_molfile_text


def molfiles_from_sdf(sdf_path: str) -> list[str]:
    """
    TODO: How to implement a lazy fixture?
    I.e., fixture that yields single molfiles one by one,
    instead of a list of molfiles, in order to reduce the memory footprint of the test.

    https://stackoverflow.com/questions/54163532/lazy-parametrization-with-pytest
    """

    molfile_strings = []
    current_molfile = ""
    with gzip.open(sdf_path, "rb") as gzipped_sdf:
        for gunzipped_line in gzipped_sdf:
            line = gunzipped_line.decode("utf-8", "backslashreplace")
            if "$$$$" in line:
                molfile_strings.append(current_molfile)
                current_molfile = ""
            else:
                current_molfile += line

    return molfile_strings


def get_molfile_id(molfile):
    return molfile.split()[0].strip()


@pytest.mark.parametrize(
    "molfile", molfiles_from_sdf("testdata/default_testset.sdf.gz"), ids=get_molfile_id
)
@pytest.mark.parametrize(
    "options", ["-NEWPSOFF", "-SNon", "-DoNotAddH", "-SNon -DoNotAddH"]
)
def test_regression_standard(molfile, options, snapshot):
    _, inchi_string, _, _, _ = make_inchi_from_molfile_text(molfile, options)
    assert inchi_string == snapshot
