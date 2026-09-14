#!/usr/bin/env bash

set -e

EXE="$1"
DIST="$2"

mkdir -p "$DIST"

declare -A copied

copy_deps()
{
    local file="$1"

    while read -r line; do

        dll=$(echo "$line" | sed -n 's/.*=> \([^ ]*\.dll\).*/\1/p')

        if [[ -z "$dll" ]]; then
            continue
        fi

        dll=$(cygpath -w "$dll" 2>/dev/null || echo "$dll")

        if [[ ! -f "$dll" ]]; then
            continue
        fi

        name=$(basename "$dll")

        if [[ "${copied[$name]}" == "1" ]]; then
            continue
        fi

        copied[$name]=1

        echo "Copying $name"

        cp "$dll" "$DIST/$name"

        copy_deps "$dll"

    done < <(ldd "$file")
}

echo "Collecting dependencies..."

copy_deps "$EXE"

echo "Done."