from setuptools import setup, Extension

module = Extension('summodule', sources=['library.c'])

setup(
    name='SumModule',
    version='1.0',
    description='Python Package with C Extension for summing arrays',
    ext_modules=[module]
)

