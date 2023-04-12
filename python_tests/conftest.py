import pytest
import gzip
from typing import Iterator

# TODO: harden SDF parsing according to http://www.dalkescientific.com/writings/diary/archive/2020/09/18/handling_the_sdf_record_delimiter.html


def molfiles_from_sdf(sdf_path: str) -> Iterator[str]:
    current_molfile = ""
    with gzip.open(sdf_path, "rb") as gzipped_sdf:
        for gunzipped_line in gzipped_sdf:
            line = gunzipped_line.decode("utf-8", "backslashreplace")
            if "$$$$" in line:
                yield current_molfile
                current_molfile = ""
            else:
                current_molfile += line


def count_molfiles_in_sdf(sdf_path: str) -> int:
    return 2


def pytest_addoption(parser):
    parser.addoption(
        "--sdf-path",
        action="store",
        required=True,
        help="Relative path to a gzipped SDF (relative/path/to/mymolfiles.sdf.gz).",
    )


def pytest_configure(config):
    sdf_path = config.getoption("--sdf-path")
    n_molfiles = count_molfiles_in_sdf(sdf_path)

    class Plugin:
        """https://github.com/pytest-dev/pytest/issues/5027"""

        def __init__(self) -> None:
            self._molfiles = molfiles_from_sdf(sdf_path)

        @pytest.fixture(
            scope="function", params=range(n_molfiles)
        )  # TODO: clarify scope
        def molfile(self):
            """
            This fixture is lazy, i.e., it yields / generates single molfiles:
            https://stackoverflow.com/questions/54163532/lazy-parametrization-with-pytest

            Otherwise, pytest doesn't allow for parametrization with generators,
            since it turns generators that are passed to `@pytest.mark.parametrize`
            into lists during test collection.
            Depending on the size of the SDF, this list can be very large,
            resulting in an unacceptable memory footprint of the test:
            https://github.com/pytest-dev/pytest/issues/3070
            https://github.com/pytest-dev/pytest/issues/5640
            """

            molfile = next(self._molfiles)
            print(molfile)

            return molfile

    config.pluginmanager.register(Plugin())
