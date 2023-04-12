import pytest
from inchi_api import make_inchi_from_molfile_text


@pytest.mark.parametrize(
    "options", ["-NEWPSOFF", "-SNon", "-DoNotAddH", "-SNon -DoNotAddH"]
)
def test_regression_standard(molfile, options, snapshot):
    """Run with `--snapshot-update` to update snapshots."""
    _, inchi_string, _, _, _ = make_inchi_from_molfile_text(molfile, options)
    assert inchi_string == snapshot  # TODO: log results using pytest-reportlog
