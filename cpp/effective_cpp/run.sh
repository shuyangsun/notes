cd ./build
for FILE in *; do
    [[ "$FILE" =~ ^item_[0-9]+$ ]] && "./$FILE"
done
