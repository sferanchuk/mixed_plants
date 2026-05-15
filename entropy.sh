
for key in control mint thyme achillea cacalia panzeria xerochrysum karagana thyme_mint cacalia_achillea thyme_cacalia mint_achillea panzeria_xerochrysum panzeria_karagana xerochrysum_karagana
do
	s=0
	s2=0
	n=0
	for f in ${key}_?.png
	do 
		e=`../fdim_entr2 $f`
		e2=`../fdim_entr1 $f`
		s=`echo "$s+$e" | bc -l`
		s2=`echo "$s2+$e2" | bc -l`
		n=$(($n+1))
	done
	ss=`echo "$s/$n" | bc -l`
	ss2=`echo "$s2/$n" | bc -l`
	echo $key $ss2 $ss
done
	