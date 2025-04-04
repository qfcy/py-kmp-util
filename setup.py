import sys,os,shutil,subprocess,shlex
from setuptools import setup, Extension

if "sdist" in sys.argv[1:]:
    if not os.path.isfile("README.rst") or \
       (os.stat("README.md").st_mtime > os.stat("README.rst").st_mtime):
        if shutil.which("pandoc"):
            cmd="pandoc -t rst -o README.rst README.md" # Generate README.rst
            print("Running pandoc:",cmd,"...")
            result=subprocess.run(shlex.split(cmd))
            print("Return code:",result.returncode)
        else:
            print("Pandoc command for generating README.rst is required",
                  file=sys.stderr)
            sys.exit(1)

if os.path.isfile("README.rst"):
    long_desc=open("README.rst",encoding="utf-8").read()
else:
    long_desc=""

# Define the C extension
kmp_util_module = Extension(
    "kmp_util",
    sources=["kmp_util.c"],
)

# Setup script
setup(
    name="kmp_util",
    version="1.0.1",
    description="A module that provides KMP-based search for strings and bytes.",
    long_description=long_desc,
    author="qfcy",
    author_email="3076711200@qq.com",
    url="https://github.com/qfcy/py-kmp-util",
    ext_modules=[kmp_util_module],
    keywords=["kmp","string","algorithm"],
)