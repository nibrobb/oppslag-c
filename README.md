# Kjøretøy Oppslag

## Quick start

**Note: only available for Norwegian citizens.**

To use this project you need an API-key from the Norwegian Road Authority (Statens Vegvesen) vehicle lookup service, which you may apply for [here](https://www.vegvesen.no/kjoretoy/kjop-og-salg/kjoretoyopplysninger/api-er-for-tekniske-kjoretoyopplysninger/api-for-tekniske-kjoretoyopplysninger/). 

Dependencies include `gcc`, `jq` and `libcurl-dev`

To install dependencies on Ubuntu 22.04 LTS
```bash
sudo apt install gcc jq libcurl4-openssl-dev
```

## Compile and run
Simply compile with the included build-script
```bash
./build.sh
```

The program may be run with the license plate as a commandline argument

```bash
./oppslag [LICENSE PLATE]
```

Or via stdin
```bash
echo "AB12345" | ./oppslag
```


