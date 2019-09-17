# PHP7 GDAL

## Dependencies
- GDAL-dev (>v2.0)
- PHPCPP (v2.1.4)
- PHP7.0-dev

### Installing Dependencies
- ```sudo apt install libgdal-dev```
- ```sudo apt install php7.0-dev```
    - If the package isn't available in your distro, take a look [here](https://deb.sury.org/)
- PHPCPP can be found [here](https://github.com/CopernicaMarketingSoftware/PHP-CPP)

## Installation
- Requirements
   - PHP7.0

## Building the extension
-   Clone this repository
-   ```cd php7-gdal && make```
-   If all goes well, you should then be able to do ```sh deploy.sh``` which will copy your extension to the PHP extension directory

## Tests
- In lieu of PHPUnit, I've included a small test script which will do for now.
- ```make test```

## Examples
- View ```examples/example.php``` in the repo.

