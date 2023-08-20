from setuptools import setup, Extension
try:
    from pybind11.setup_helpers import Pybind11Extension, build_ext
except ImportError:
    from setuptools import Extension as Pybind11Extension, build_ext
# from pybind11.setup_helpers import Pybind11Extension, build_ext

setup(
    name='geo',
    version='0.1',
    author = "Aromal M A",
    author_email = "aromalma@yahoo.com",
    cmdclass={"build_ext": build_ext},
    ext_modules=[Pybind11Extension('geo', ['geo.cpp'])],
    zip_safe=False,
)