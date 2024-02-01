# Kjøretøy Oppslag

## Quick start

To use this project you need an API-key for the vehicle lookup service, which you may apply for [here](https://www.vegvesen.no/kjoretoy/kjop-og-salg/kjoretoyopplysninger/api-er-for-tekniske-kjoretoyopplysninger/api-for-tekniske-kjoretoyopplysninger/)
Dependencies include `gcc` and `libcurl-dev`

To install libcurl on Ubuntu 22.04 LTS
```bash
sudo apt install gcc make libcurl4-openssl-dev
```

## Running
Oppslag may be run with the license plate as a commandline argument

```bash
./oppslag [LICENSE PLATE]
```

Or via stdin
```bash
echo "AB12345" | ./oppslag
```


