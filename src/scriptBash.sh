#!/bin/bash

EXECUTABLE="test"

OPTIONS_FILE="option.txt"

RESULTS_FILE="resultats_compilations.txt"

if [ ! -f "$OPTIONS_FILE" ]; then
    echo "Le fichier des options $OPTIONS_FILE n'existe pas."
    exit 1
fi

echo "Résultats des tests de compilation et d'exécution" > "$RESULTS_FILE"
echo "------------------------------------------------" >> "$RESULTS_FILE"

while IFS= read -r OPTIONS; do
    echo "Options de compilation: $OPTIONS" | tee -a "$RESULTS_FILE"
    
    g++ $OPTIONS -std=c++17 *.cpp -o "$EXECUTABLE"
    
    if [ $? -ne 0 ]; then
        echo "Échec de la compilation avec les options: $OPTIONS" | tee -a "$RESULTS_FILE"
        continue
    fi
    
    OUTPUT=$(./"$EXECUTABLE")
    EXIT_STATUS=$?
    
    if [ $EXIT_STATUS -ne 0 ]; then
        echo "Échec de l'exécution avec les options: $OPTIONS" | tee -a "$RESULTS_FILE"
    else
        echo "Sortie du programme:" >> "$RESULTS_FILE"
        echo "$OUTPUT" >> "$RESULTS_FILE"
    fi
    
    echo "------------------------------------------------" >> "$RESULTS_FILE"
done < "$OPTIONS_FILE"

echo "Tests terminés. Les résultats sont enregistrés dans $RESULTS_FILE."
