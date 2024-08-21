#!/bin/bash

OUTPUT=utests.output

./testsuite > "$OUTPUT" 2>/dev/null

if [ ! -s "$OUTPUT" ] ; then
    echo "UNIT FAIL (testsuite produced no output)"
    rm -f "$OUTPUT"
    exit 1
fi

cat "$OUTPUT" | awk '/Failures/,0'

percent=$(cat "$OUTPUT" | grep Failures | cut -d':' -f1)
rm -f "$OUTPUT"
[ "$percent" = "100%" ] && exit 0

echo "(run ./testsuite in tests directory for more information)"
exit 1

