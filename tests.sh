export TEST_FILE="fichier_vide"

./ft_otool tests/hell/$TEST_FILE > mon_otool.txt && otool -t tests/hell/$TEST_FILE > native_otool.txt && diff mon_otool.txt native_otool.txt