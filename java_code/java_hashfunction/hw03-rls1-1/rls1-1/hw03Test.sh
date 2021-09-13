java Hw03 oneA.txt > oneASt.txt
diff oneASt.txt oneASt.txt
echo "oneA.txt complete"

java Hw03 twoAs.txt > twoAsSt.txt
diff twoAsSt.txt  twoAsValid.txt
echo "twoAs.txt complete"

java Hw03 threeAs.txt > threeAsSt.txt
diff threeAsSt.txt  threeAsValid.txt
echo "threeAs.txt complete"

java Hw03 fourAs.txt > fourAsSt.txt
diff fourAsSt.txt  fourAsValid.txt
echo "fourAs.txt complete"

java Hw03 5words.txt > 5wordsSt.txt
diff 5wordsSt.txt  5wordsValid.txt
echo "5words.txt complete"

java Hw03 100words.txt > 100wordsSt.txt
diff 100wordsSt.txt  100wordsValid.txt
echo "100words.txt complete"

java Hw03 500words.txt > 500wordsSt.txt
diff 500wordsSt.txt  500wordsValid.txt
echo "500words.txt complete"

java Hw03 1000words.txt > 1000wordsSt.txt
diff 1000wordsSt.txt  1000wordsValid.txt
echo "1000words.txt complete"

java Hw03 2500words.txt > 2500wordsSt.txt
diff 2500wordsSt.txt  2500wordsValid.txt
echo "2500words.txt complete"
