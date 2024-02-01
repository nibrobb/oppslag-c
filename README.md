# Kjøretøy Oppslag

## Quick start

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


