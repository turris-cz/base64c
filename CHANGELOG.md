# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [0.2.1] - 2021-05-28
### Added
- Linker's version script to limit exported symbols

### Changed
- Configure now fails if linters are enabled and `cppcheck` is not available

### Fixed
- Distribution archives
- Version in pkg-config file


## [0.2.0] - 2020-07-23
### Changed
- `base64_valid` renamed to `bas64_verify` and return value meaning changed
- `base64_str_valid` renamed to `base64_str_verify` and return value is now
  `size_t` (same as `base64_valid`).


## [0.1.0] - 2020-07-22
### Added
- Initial version of base64c with unstable API for now
