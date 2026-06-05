#!/bin/bash

shopt -s nullglob
shopt -s globstar

if [[ "$1" == "--show-valid" || "$1" == "-sv" ]]; then
    VALID=1
else
    VALID=0
fi

TOTAL_LINE=$(cat **/*.c **/*.h *.c *.h 2>/dev/null | wc -l)
if [ "$TOTAL_LINE" -eq 0 ]; then
    echo "No .c or .h files"
    exit 1
fi

TOTAL_ERROR=$(norminette | grep "Error:" | wc -l)
TOTAL_RATIO=$(echo "scale=2; ($TOTAL_ERROR / $TOTAL_LINE) * 100" | bc)
TOTAL_FILE=$(set -- **/*.c **/*.h; echo $#)

echo "======================================================"
echo "📊 RATIO ERROR : $TOTAL_ERROR on $TOTAL_LINE lines for $TOTAL_FILE files"
echo "📈 $TOTAL_RATIO%"
echo "======================================================"

check_norme_recursive()
{
    local target="$1"
    local indent="$2"

    if [[ "$(basename "$target")" == .* ]]; then
        return
    fi

    local errs=$(norminette "$target" 2>/dev/null | grep "Error:" | wc -l)

    local ratio="0"
    if [ "$TOTAL_ERROR" -gt 0 ]; then
        ratio=$(echo "scale=2; ( $errs * 100 / $TOTAL_ERROR )" | bc)
    fi

    if [ -d "$target" ]; then
        if [ "$errs" -eq 0 ]; then
            if [ "$VALID" -eq 1 ]; then
                echo "${indent}✅ - $target/ -> 0 errors"
            fi
            return
        else 
            echo "${indent}❌ - $target/ -> $errs errors ($ratio% du total)"

            for child in "$target"/*; do
                check_norme_recursive "$child" "$indent  "
            done
        fi

    elif [ -f "$target" ] && [[ "$target" == *.c || "$target" == *.h ]]; then
        if [ "$errs" -eq 0 ]; then
            if [ "$VALID" -eq 1 ]; then
                echo "${indent}✅ - $target -> 0 errors"
            fi
        else 
            echo "${indent}❌ - $target -> $errs errors ($ratio% du total)"
        fi
    fi
}

for item in *; do
    check_norme_recursive "$item" ""
done
