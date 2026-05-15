
of="mixtures.html"
echo "<html><body><table>" >$of
echo "<tr><td>control" >>$of
magick sources/control/20260122095807975.png -crop 256x192+200+200 -colorspace Gray control_1.png
echo "<td><img src=\"control_1.png\" />" >>$of
magick sources/control/20260122095807975.png -crop 256x192+1000+600 -colorspace Gray control_2.png
echo "<td><img src=\"control_2.png\" />" >>$of
magick sources/control/20260430091954301.png -crop 256x192+1000+100 -colorspace Gray control_3.png
echo "<td><img src=\"control_3.png\" />" >>$of
magick sources/control/20260430091954301.png -crop 256x192+1000+600 -colorspace Gray control_4.png
echo "<td><img src=\"control_4.png\" />" >>$of
echo "<tr><td>mint" >>$of
magick sources/mint/20260429105405075.png -crop 256x192+100+100 -colorspace Gray mint_1.png
echo "<td><img src=\"mint_1.png\" />" >>$of
magick sources/mint/20260429105405075.png -crop 256x192+700+100 -colorspace Gray mint_2.png
echo "<td><img src=\"mint_2.png\" />" >>$of
magick sources/mint/20260429105414905.png -crop 256x192+100+800 -colorspace Gray mint_3.png
echo "<td><img src=\"mint_3.png\" />" >>$of
magick sources/mint/20260429105414905.png -crop 256x192+1000+100 -colorspace Gray mint_4.png
echo "<td><img src=\"mint_4.png\" />" >>$of
echo "<tr><td>thyme" >>$of
magick sources/thyme/20260429105146573.png -crop 256x192+100+700 -colorspace Gray thyme_1.png
echo "<td><img src=\"thyme_1.png\" />" >>$of
magick sources/thyme/20260429105146573.png -crop 256x192+1000+300 -colorspace Gray thyme_2.png
echo "<td><img src=\"thyme_2.png\" />" >>$of
magick sources/thyme/20260429105221819.png -crop 256x192+100+700 -colorspace Gray thyme_3.png
echo "<td><img src=\"thyme_3.png\" />" >>$of
magick sources/thyme/20260429105221819.png -crop 256x192+1000+300 -colorspace Gray thyme_4.png
echo "<td><img src=\"thyme_4.png\" />" >>$of
echo "<tr><td>achillea" >>$of
magick sources/achillea/20260429104616471.png -crop 256x192+100+100 -colorspace Gray achillea_1.png
echo "<td><img src=\"achillea_1.png\" />" >>$of
magick sources/achillea/20260429104616471.png -crop 256x192+100+1300 -colorspace Gray achillea_2.png
echo "<td><img src=\"achillea_2.png\" />" >>$of
magick sources/achillea/20260429104634263.png -crop 256x192+700+100 -colorspace Gray achillea_3.png
echo "<td><img src=\"achillea_3.png\" />" >>$of
magick sources/achillea/20260429104634263.png -crop 256x192+200+1000 -colorspace Gray achillea_4.png
echo "<td><img src=\"achillea_4.png\" />" >>$of
echo "<tr><td>cacalia" >>$of
magick sources/cacalia/20260430091422234.png -crop 256x192+600+1200 -colorspace Gray cacalia_1.png
echo "<td><img src=\"cacalia_1.png\" />" >>$of
magick sources/cacalia/20260430091422234.png -crop 256x192+800+1200 -colorspace Gray cacalia_2.png
echo "<td><img src=\"cacalia_2.png\" />" >>$of
magick sources/cacalia/20260430091429053.png -crop 256x192+600+1200 -colorspace Gray cacalia_3.png
echo "<td><img src=\"cacalia_3.png\" />" >>$of
magick sources/cacalia/20260430091429053.png -crop 256x192+800+1200 -colorspace Gray cacalia_4.png
echo "<td><img src=\"cacalia_4.png\" />" >>$of
echo "<tr><td>panzeria" >>$of
magick sources/panzeria/20260512190758118.png -crop 256x192+1400+100 -colorspace Gray panzeria_1.png
echo "<td><img src=\"panzeria_1.png\" />" >>$of
magick sources/panzeria/20260512190758118.png -crop 256x192+1000+800 -colorspace Gray panzeria_2.png
echo "<td><img src=\"panzeria_2.png\" />" >>$of
magick sources/panzeria/20260512190808045.png -crop 256x192+1400+100 -colorspace Gray panzeria_3.png
echo "<td><img src=\"panzeria_3.png\" />" >>$of
magick sources/panzeria/20260512190808045.png -crop 256x192+1200+600 -colorspace Gray panzeria_4.png
echo "<td><img src=\"panzeria_4.png\" />" >>$of
echo "<tr><td>xerochrysum" >>$of
magick sources/xerochrysum/20260511094958085.png -crop 256x192+1320+330 -colorspace Gray xerochrysum_1.png
echo "<td><img src=\"xerochrysum_1.png\" />" >>$of
magick sources/xerochrysum/20260511094958085.png -crop 256x192+1180+680 -colorspace Gray xerochrysum_2.png
echo "<td><img src=\"xerochrysum_2.png\" />" >>$of
magick sources/xerochrysum/20260511095130948.png -crop 256x192+1190+360 -colorspace Gray xerochrysum_3.png
echo "<td><img src=\"xerochrysum_3.png\" />" >>$of
magick sources/xerochrysum/20260511095130948.png -crop 256x192+1140+460 -colorspace Gray xerochrysum_4.png
echo "<td><img src=\"xerochrysum_4.png\" />" >>$of
echo "<tr><td>karagana" >>$of
magick sources/karagana/20260511092635424.png -crop 256x192+50+500 -colorspace Gray karagana_1.png
echo "<td><img src=\"karagana_1.png\" />" >>$of
magick sources/karagana/20260511092635424.png -crop 256x192+1000+200 -colorspace Gray karagana_2.png
echo "<td><img src=\"karagana_2.png\" />" >>$of
magick sources/karagana/20260511093009926.png -crop 256x192+100+50 -colorspace Gray karagana_3.png
echo "<td><img src=\"karagana_3.png\" />" >>$of
magick sources/karagana/20260511093009926.png -crop 256x192+1000+400 -colorspace Gray karagana_4.png
echo "<td><img src=\"karagana_4.png\" />" >>$of
echo "<tr><td>thyme + mint" >>$of
magick sources/thyme_mint/20260505200812458.png -crop 256x192+800+100 -colorspace Gray thyme_mint_1.png
echo "<td><img src=\"thyme_mint_1.png\" />" >>$of
magick sources/thyme_mint/20260505200812458.png -crop 256x192+50+1200 -colorspace Gray thyme_mint_2.png
echo "<td><img src=\"thyme_mint_2.png\" />" >>$of
magick sources/thyme_mint/20260505200834960.png -crop 256x192+1200+100 -colorspace Gray thyme_mint_3.png
echo "<td><img src=\"thyme_mint_3.png\" />" >>$of
magick sources/thyme_mint/20260505200834960.png -crop 256x192+1200+1000 -colorspace Gray thyme_mint_4.png
echo "<td><img src=\"thyme_mint_4.png\" />" >>$of
echo "<tr><td>cacalia + achillea" >>$of
magick sources/cacalia_achillea/20260505202332329.png -crop 256x192+100+500 -colorspace Gray cacalia_achillea_1.png
echo "<td><img src=\"cacalia_achillea_1.png\" />" >>$of
magick sources/cacalia_achillea/20260505202332329.png -crop 256x192+1000+50 -colorspace Gray cacalia_achillea_2.png
echo "<td><img src=\"cacalia_achillea_2.png\" />" >>$of
magick sources/cacalia_achillea/20260505202340081.png -crop 256x192+100+800 -colorspace Gray cacalia_achillea_3.png
echo "<td><img src=\"cacalia_achillea_3.png\" />" >>$of
magick sources/cacalia_achillea/20260505202340081.png -crop 256x192+1000+500 -colorspace Gray cacalia_achillea_4.png
echo "<td><img src=\"cacalia_achillea_4.png\" />" >>$of
echo "<tr><td>thyme + cacalia" >>$of
magick sources/thyme_cacalia/20260505201735587.png -crop 256x192+250+150 -colorspace Gray thyme_cacalia_1.png
echo "<td><img src=\"thyme_cacalia_1.png\" />" >>$of
magick sources/thyme_cacalia/20260505201735587.png -crop 256x192+1600+50 -colorspace Gray thyme_cacalia_2.png
echo "<td><img src=\"thyme_cacalia_2.png\" />" >>$of
magick sources/thyme_cacalia/20260505201755340.png -crop 256x192+50+500 -colorspace Gray thyme_cacalia_3.png
echo "<td><img src=\"thyme_cacalia_3.png\" />" >>$of
magick sources/thyme_cacalia/20260505201755340.png -crop 256x192+1050+100 -colorspace Gray thyme_cacalia_4.png
echo "<td><img src=\"thyme_cacalia_4.png\" />" >>$of
echo "<tr><td>mint + achillea" >>$of
magick sources/mint_achillea/20260505203015445.png -crop 256x192+1000+100 -colorspace Gray mint_achillea_1.png
echo "<td><img src=\"mint_achillea_1.png\" />" >>$of
magick sources/mint_achillea/20260505203015445.png -crop 256x192+200+1000 -colorspace Gray mint_achillea_2.png
echo "<td><img src=\"mint_achillea_2.png\" />" >>$of
magick sources/mint_achillea/20260505203047850.png -crop 256x192+1000+100 -colorspace Gray mint_achillea_3.png
echo "<td><img src=\"mint_achillea_3.png\" />" >>$of
magick sources/mint_achillea/20260505203047850.png -crop 256x192+100+1000 -colorspace Gray mint_achillea_4.png
echo "<td><img src=\"mint_achillea_4.png\" />" >>$of
echo "<tr><td>panzeria + xerochrysum" >>$of
magick sources/panzeria_xerochrysum/20260511094603643.png -crop 256x192+900+100 -colorspace Gray panzeria_xerochrysum_1.png
echo "<td><img src=\"panzeria_xerochrysum_1.png\" />" >>$of
magick sources/panzeria_xerochrysum/20260511094603643.png -crop 256x192+650+900 -colorspace Gray panzeria_xerochrysum_2.png
echo "<td><img src=\"panzeria_xerochrysum_2.png\" />" >>$of
magick sources/panzeria_xerochrysum/20260511094646540.png -crop 256x192+200+650 -colorspace Gray panzeria_xerochrysum_3.png
echo "<td><img src=\"panzeria_xerochrysum_3.png\" />" >>$of
magick sources/panzeria_xerochrysum/20260511094646540.png -crop 256x192+1500+250 -colorspace Gray panzeria_xerochrysum_4.png
echo "<td><img src=\"panzeria_xerochrysum_4.png\" />" >>$of
echo "<tr><td>panzeria + karagana" >>$of
magick sources/karagana_panzeria/20260511093951320.png -crop 256x192+200+750 -colorspace Gray panzeria_karagana_1.png
echo "<td><img src=\"panzeria_karagana_1.png\" />" >>$of
magick sources/karagana_panzeria/20260511093951320.png -crop 256x192+1550+750 -colorspace Gray panzeria_karagana_2.png
echo "<td><img src=\"panzeria_karagana_2.png\" />" >>$of
magick sources/karagana_panzeria/20260511094006507.png -crop 256x192+200+900 -colorspace Gray panzeria_karagana_3.png
echo "<td><img src=\"panzeria_karagana_3.png\" />" >>$of
magick sources/karagana_panzeria/20260511094006507.png -crop 256x192+1450+1100 -colorspace Gray panzeria_karagana_4.png
echo "<td><img src=\"panzeria_karagana_4.png\" />" >>$of
echo "<tr><td>xerochrysum + karagana" >>$of
magick sources/karagana_xerochrysum/20260511175343975.png -crop 256x192+100+100 -colorspace Gray xerochrysum_karagana_1.png
echo "<td><img src=\"xerochrysum_karagana_1.png\" />" >>$of
magick sources/karagana_xerochrysum/20260511175343975.png -crop 256x192+1400+1000 -colorspace Gray xerochrysum_karagana_2.png
echo "<td><img src=\"xerochrysum_karagana_2.png\" />" >>$of
magick sources/karagana_xerochrysum/20260511175534112.png -crop 256x192+50+600 -colorspace Gray xerochrysum_karagana_3.png
echo "<td><img src=\"xerochrysum_karagana_3.png\" />" >>$of
magick sources/karagana_xerochrysum/20260511175534112.png -crop 256x192+1000+600 -colorspace Gray xerochrysum_karagana_4.png
echo "<td><img src=\"xerochrysum_karagana_4.png\" />" >>$of

echo "</table></body></html>" >>$of