from setuptools import setup, Extension
try:
    from pybind11.setup_helpers import Pybind11Extension
except ImportError:
    from setuptools import Extension as Pybind11Extension

setup(
    name='geo',
    version='0.1',
    ext_modules=[Pybind11Extension('geo', ['geo.cpp'])],
    zip_safe=False,
)