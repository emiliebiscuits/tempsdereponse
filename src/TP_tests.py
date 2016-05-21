import os;

def main():
	print("\n###################################")
	print("##### LANCEMENT DU TEST PYTHON ####")
	print("###################################")

	print("\n===================================")
	print("| 1] TESTS NON VERBOSE SUR STDOUT |")
	print("===================================\n")

	print("TEST 1 : Attente active, 100 tests, 1000 microsecondes")
	os.system("./TP_reel 100 1 1000 0")
	print("TEST 2 : Attente active, 100 tests, 100 microsecondes")
	os.system("./TP_reel 100 1 100 0")
	print("TEST 3 : Attente active, 500 tests, 1000 microsecondes")
	os.system("./TP_reel 500 1 1000 0")
	print("TEST 4 : Attente active, 500 tests, 100 microsecondes")
	os.system("./TP_reel 500 1 100 0")
	print("TEST 5 : Attente passive, 100 tests, 1000 microsecondes")
	os.system("./TP_reel 100 0 1000 0")
	print("TEST 6 : Attente passive, 100 tests, 100 microsecondes")
	os.system("./TP_reel 100 0 100 0")
	print("TEST 7 : Attente passive, 500 tests, 1000 microsecondes")
	os.system("./TP_reel 500 0 1000 0")
	print("TEST 8 : Attente passive, 500 tests, 100 microsecondes")
	os.system("./TP_reel 500 0 100 0")



	print("\n===================================")
	print("|   2] TESTS VERBOSE SUR STDOUT   |")
	print("===================================\n")

	print("TEST 1 : Attente active, 100 tests, 1000 microsecondes")
	os.system("./TP_reel 100 1 1000 0 --verbose")
	print("TEST 2 : Attente active, 100 tests, 100 microsecondes")
	os.system("./TP_reel 100 1 100 0 --verbose")
	print("TEST 3 : Attente active, 500 tests, 1000 microsecondes")
	os.system("./TP_reel 500 1 1000 0 --verbose")
	print("TEST 4 : Attente active, 500 tests, 100 microsecondes")
	os.system("./TP_reel 500 1 100 0")
	print("TEST 5 : Attente passive, 100 tests, 1000 microsecondes")
	os.system("./TP_reel 100 0 1000 0 --verbose")
	print("TEST 6 : Attente passive, 100 tests, 100 microsecondes")
	os.system("./TP_reel 100 0 100 0 --verbose")
	print("TEST 7 : Attente passive, 500 tests, 1000 microsecondes")
	os.system("./TP_reel 500 0 1000 0 --verbose")
	print("TEST 8 : Attente passive, 500 tests, 100 microsecondes")
	os.system("./TP_reel 500 0 100 0 --verbose")



	print("\n===================================")
	print("| 3] TESTS NON VERBOSE SUR FICHIER|")
	print("===================================\n")

	print("TEST 9 : Attente active, 100 tests, 1000 microsecondes")
	os.system("./TP_reel 100 1 1000 1")
	print("TEST 10 : Attente active, 100 tests, 100 microsecondes")
	os.system("./TP_reel 100 1 100 1")
	print("TEST 11 : Attente active, 500 tests, 1000 microsecondes")
	os.system("./TP_reel 500 1 1000 1")
	print("TEST 12 : Attente active, 500 tests, 100 microsecondes")
	os.system("./TP_reel 500 1 100 1")
	print("TEST 13 : Attente passive, 100 tests, 1000 microsecondes")
	os.system("./TP_reel 100 0 1000 1")
	print("TEST 14 : Attente passive, 100 tests, 100 microsecondes")
	os.system("./TP_reel 100 0 100 1")
	print("TEST 15 : Attente passive, 500 tests, 1000 microsecondes")
	os.system("./TP_reel 500 0 1000 1")
	print("TEST 16 : Attente passive, 500 tests, 100 microsecondes")
	os.system("./TP_reel 500 0 100 1")



	print("\n===================================")
	print("|  4] TESTS VERBOSE SUR FICHIER   |")
	print("===================================\n")

	print("TEST 17 : Attente active, 100 tests, 1000 microsecondes")
	os.system("./TP_reel 100 1 1000 1 --verbose")
	print("TEST 18 : Attente active, 100 tests, 100 microsecondes")
	os.system("./TP_reel 100 1 100 1 --verbose")
	print("TEST 19 : Attente active, 500 tests, 1000 microsecondes")
	os.system("./TP_reel 500 1 1000 1 --verbose")
	print("TEST 20 : Attente active, 500 tests, 100 microsecondes")
	os.system("./TP_reel 500 1 100 1")
	print("TEST 21 : Attente passive, 100 tests, 1000 microsecondes")
	os.system("./TP_reel 100 0 1000 1 --verbose")
	print("TEST 22 : Attente passive, 100 tests, 100 microsecondes")
	os.system("./TP_reel 100 0 100 1 --verbose")
	print("TEST 23 : Attente passive, 500 tests, 1000 microsecondes")
	os.system("./TP_reel 500 0 1000 1 --verbose")
	print("TEST 24 : Attente passive, 500 tests, 100 microsecondes")
	os.system("./TP_reel 500 0 100 1 --verbose")


	print("\n###################################")
	print("######## FIN DU TEST PYTHON #######")
	print("###################################")
	
if __name__ == "__main__": main()
