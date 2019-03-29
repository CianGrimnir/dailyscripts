#!/bin/bash
while read num0 num2
do
	awk -v var=$num1 -v rate=$num2 -F'|' 'BEGIN{OFS="|"} $4==var{new=sprintf("%1.0f",$35);if(rate!=new) {print $0,new,rate}}' fut_contract_12122017
done < <(awk -F',' '{print $2,$3}' fo_qtyfreeze.csv)
