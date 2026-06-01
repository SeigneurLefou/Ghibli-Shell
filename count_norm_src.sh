#!/bin/bash

FILES=src/*
TOTAL_ERRORS=0
TOTAL_FILES=0
SUCCESS_FILES=0

# --- 1. PREMIER PASSAGE : CALCUL DU TOTAL DES ERREURS ---
ERRORS_INC=$(norminette includes | grep 'Error:' | wc -l)
TOTAL_ERRORS=$((TOTAL_ERRORS + ERRORS_INC))
TOTAL_FILES=$((TOTAL_FILES + 1))
if [ "$ERRORS_INC" -eq 0 ]; then SUCCESS_FILES=$((SUCCESS_FILES + 1)); fi

for file in $FILES; do
    ERRORS=$(norminette "$file" | grep "Error:" | wc -l)
    TOTAL_ERRORS=$((TOTAL_ERRORS + ERRORS))
    TOTAL_FILES=$((TOTAL_FILES + 1))
    if [ "$ERRORS" -eq 0 ]; then SUCCESS_FILES=$((SUCCESS_FILES + 1)); fi
done

# Calcul du score global de réussite
if [ $TOTAL_FILES -gt 0 ]; then
    SCORE_GLOBAL=$(( SUCCESS_FILES * 100 / TOTAL_FILES ))
else
    SCORE_GLOBAL=0
fi

# --- 2. AFFICHAGE DU HEADER ---
echo "======================================================"
echo "📊 TOTAL ERREURS : $TOTAL_ERRORS"
echo "📈 REUSSITE GLOBALE : $SCORE_GLOBAL% de fichiers valides ($SUCCESS_FILES/$TOTAL_FILES)"
echo "======================================================"
echo ""

# --- 3. SECOND PASSAGE : AFFICHAGE DÉTAILLÉ AVEC PRORATA ---

# Fonction pour calculer et formater le pourcentage individuel
get_ratio() {
    local err=$1
    if [ "$TOTAL_ERRORS" -eq 0 ]; then
        echo "0%"
    else
        echo "$(( err * 100 / TOTAL_ERRORS ))%"
    fi
}

# Affichage pour includes/
RATIO_INC=$(get_ratio "$ERRORS_INC")
if [ "$ERRORS_INC" -eq 0 ]; then
    echo "✅ - includes/ -> $ERRORS_INC error.s ($RATIO_INC du total)"
else
    echo "❌ - includes/ -> $ERRORS_INC error.s ($RATIO_INC du total)"
fi

# Affichage pour les fichiers dans src/
for file in $FILES; do
    ERRORS=$(norminette "$file" | grep "Error:" | wc -l)
    RATIO=$(get_ratio "$ERRORS")
    
    if [ "$ERRORS" -eq 0 ]; then
        echo "✅ - $file -> $ERRORS error.s ($RATIO du total)"
    else
        echo "❌ - $file -> $ERRORS error.s ($RATIO du total)"
    fi
done
