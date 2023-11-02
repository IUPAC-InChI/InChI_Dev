# `InChI v.1.07 (Beta)` release notes

 ![CI](https://github.com/IUPAC-InChI/InChI_Dev/actions/workflows/ci.yml/badge.svg)

## Using precompiled binaries
Precompiled binaries (executable, `.dll/.so` and ELF files) are located in the following folders:
<br />
<table id="Win">
  <tr>
    <td colspan="3" align="center"><strong>Microsoft<sup>&reg;</sup> Windows</strong></td>
  </tr>
  <tr>
    <td>
      <strong>Files</strong>
    </td>
    <td>
      <strong>Compiler</strong>
    </td>
    <td>
      <strong>Folder</strong>
    </td>
  </tr>
  <tc>
    <td rowspan="2">
      <code>inchi-1.exe</code>
    </td>
    <td>
      <code>Microsoft<sup>&reg;</sup> Visual Studio C++ (MSVC)/Clang/LLVM</code>
    </td>
    <td>
      <code>/INCHI_EXE/bin2/Windows/x64/Release</code>
    </td>
  </tr>
  <tr>
    <td>
      <code>GCC/Clang(LLVM)</code>
    </td>
    <td>
      <code>/INCHI_EXE/bin/Linux</code>
    </td>
  </tr>
  <tc>
    <td rowspan="2">
      <code>libinchi.dll</code> + corresponding <code>inchi_main.exe</code>
    </td>
    <td>
      <code>Microsoft<sup>&reg;</sup> Visual Studio C++ (MSVC)/Clang/LLVM</code>
    </td>
    <td>
      <code>/INCHI_API/bin2/Windows/x64/Release</code>
    </td>
  </tr>
  <tr>
    <td>
      <code>GCC/Clang(LLVM)</code>
    </td>
    <td>
      <code>/INCHI_API/bin/Linux</code>
    </td>
  </tr>
</table>
<br />
<table id="OtherOS">
  <tr>
    <td colspan="3" align="center"><strong>UNIX-based OSs and MacOS<sup>&reg;</sup></strong></td>
  </tr>
  <tr>
    <td>
      <strong>Files</strong>
    </td>
    <td>
      <strong>Compiler</strong>
    </td>
    <td>
      <strong>Folder</strong>
    </td>
  </tr>
  <tc>
    <td>
      <code>inchi-1</code> (ELF file)
    </td>
    <td>
      <code>GCC/Clang(LLVM)</code>
    </td>
    <td>
      <code>/INCHI_EXE/bin/Linux</code>
    </td>
  </tr>
  <tc>
    <td>
      <code>libinchi.so.1.07</code> + corresponding <code>inchi_main</code> (ELF file)
    </td>
    <td>
      <code>GCC/Clang(LLVM)</code>
    </td>
    <td>
      <code>/INCHI_API/bin/Linux</code>
    </td>
  </tr>
</table>
<br />

## Compiling `InChI v.1.07` from source

Project files for Microsoft<sup>&reg;</sup> `Visual C++ (MSVC)/Clang/LLVM` users are provided for both command line and API versions of `InChI v.1.07`. The project files are located in the following folders:

- `/INCHI_EXE/inchi-1/vc14` (command line version)
- `/INCHI_API/demos/inchi_main/vc14` (API version consisting of `libinchi.dll` and its corresponding executable `inchi_main.exe`)
- `/INCHI_API/libinchi/vc14` (`libinchi.dll` only).

For other C compilers, `makefile/makefile32` files are provided in the following folders:

- `/INCHI_EXE/inchi-1/gcc` (command line version)
- `/INCHI_API/demos/inchi_main/gcc` (API version consisting of `libinchi.dll/libinchi.so.1.07` and its corresponding executable/ELF `inchi_main.exe/inchi_main`)
- `/INCHI_API/libinchi/gcc` (`libinchi.dll/libinchi.so.1.07` only).

`makefile/makefile32` files are configured to detect OSs automatically, so it is no longer needed to specify OS explicitly or run batch/bash script(s) before compiling. If both `GCC` and `Clang/LLVM` compilers are detected, `GCC` is used by default; setting `Clang/LLVM` as default compiler can be done simply by changing `CCN` parameter from `1` to `2` in `makefile/makefile32`.

If `makefile/makefile32` is used for compiling `libinchi` on Microsoft<sup>&reg;</sup> Windows, `libinchi.dll` is now generated instead of `libinchi.so.1.07`.

In order to further improve code security, [bounds checking functions](https://wiki.sei.cmu.edu/confluence/display/c/Scope) (see Annex K of [C11 standard](https://en.cppreference.com/w/c/11)) can be optionally used in `InChI v.1.07`. Since a number of C compilers (e.g. `GNU GCC`) do not support bounds checking functions, they can be installed using some of the third-party open-source libraries such as:

- [safec libc extension with all C11 Annex K functions](https://github.com/rurban/safeclib) -- actively maintained
- [Safe C lib](https://sourceforge.net/projects/safeclib/)
- [Implementation of C11 Annex K "Bounds-checking interfaces" ISO/IEC 9899:2011](https://github.com/sbaresearch/slibc)

The use of bounds checking functions in `InChI v.1.07` can be disabled in `bcf_s.h` by setting the constant `USE_BCF` to `0`.

In case `GCC` is used to compile `InChI v.1.07`, `GCC` version `11.x` is recommended, since compiling any `InChI` version (incl. `v.1.07` and `v.1.06`) using `GCC` versions `12.x` and `13.x` can produce very rare segmentation errors whilst processing several [PubChem](https://pubchem.ncbi.nlm.nih.gov/) structures. This issue will be fixed in the forthcoming update of `InChI v.1.07`.

If API version of `InChI v.1.07` is compiled using `Clang/LLVM` on `Linux` OS, `LD_LIBRARY_PATH` should be set either temporarily or permanently before `inchi_main` ELF file is used.
This can be done in several ways:

- `LD_LIBRARY_PATH` can be set temporarily:
  - by running a script titled `ldlp_fix.sh` (located in `/INCHI_API/bin/Linux`); path to `libinchi.so.1.07` can be edited in `ldlp_fix.sh`
  - using command line interface:
  
    ```
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/libinchi.so.1.07
    ```

- `LD_LIBRARY_PATH` can be set permanently:
  - by adding the following line in `~/.bashrc`:

      ```
      LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/path/to/libinchi.so.1.07"
      ```

  - by adding the `libinchi.so.1.07` path to `ld.so.conf`, which means adding a file `/etc/ld.so.conf.d/local.conf` containing just one line:

      ```
      path/to/libinchi.so.1.07
      ```

      and then running `sudo ldconfig`.
<br />

## Branches
* `main`: final debugged core files/projects
* `master`: original files as received from Igor/Gerd
