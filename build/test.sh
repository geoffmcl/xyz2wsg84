#!/bin/sh
BN=`basename $0`
TMPEXE="./xyz2wsg"
TMPEXE2="./xyz2wsg84"
if [ ! -x "$TMPEXE" ]; then
    echo "$BN: Can NOT locate $TMPEXE! *** FIX ME ***"
    exit 1
fi    

if [ ! -x "$TMPEXE2" ]; then
    echo "$BN: Can NOT locate $TMPEXE2! *** FIX ME ***"
    exit 1
fi    

echo "Some tests..."

echo ""
echo "1. Expect 6378137.0000 0.0000 0.0000"
echo "Command -r 0.0 0.0 0.0"
$TMPEXE -r 0.0 0.0 0.0
$TMPEXE2 -r 0.0 0.0 0.0

echo ""
echo "2. Expect -6378137.0000 11.1319 0.0000"
echo "Command -r 0.0 179.9999 0.0"
$TMPEXE -r 0.0 179.9999 0.0
$TMPEXE2 -r 0.0 179.9999 0.0

echo ""
echo "3. Expect 1115287.6047 -4844432.9443  3982867.0809"
echo "Command -w -r 38.889467 077.035239 149.2"
$TMPEXE -w -r 38.889467 077.035239 149.2
$TMPEXE2 -r 38.889467 -077.035239 149.2

echo ""
echo "4. Expect  39  0 37.03253  76 36 33.28940   20.25058917"
echo "Command -d 1149298.644 4827706.774 3993217.203"
$TMPEXE -d 1149298.644 4827706.774 3993217.203
$TMPEXE2 1149298.644 4827706.774 3993217.203

echo ""
echo "5. Expect -6043268.9652 -1268505.0274 -1591753.0728"
echo "Command -w -r -14.5480481694 168.1455008722 25.61"
$TMPEXE -w -r -14.5480481694 168.1455008722 25.61
$TMPEXE2 -r -14.5480481694 -168.1455008722 25.61

echo ""
echo "6. Expect 18.0000 -101.0000 -0.0008"
echo "Command -w 1157811.533 -5956423.969 1958384.474"
$TMPEXE -w 1157811.533 -5956423.969 1958384.474
$TMPEXE2  -1157811.533 -5956423.969 1958384.474

echo ""

# eof

