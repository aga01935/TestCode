################Trrigger Selection#############################


Trigger Class


CMUP10-B-NOPF-MUFAST    	runs 244980-245542

CMUP11-B-NOPF-MUFAST 	runs 245543-297595

CMUP13-B-NOPF-MUFAST 	runs 246844-246994

CMUP26-B-NOPF-MUFAST 	runs 295585-297595

CMUP6-B-NOPF-MUFAST	runs 295585-297595
Exactly 2 tracks 
Opposite charge
Pt of Muon Tracks 𝑷𝒕_𝝁 < 1 GeV
Pseudo Rapidity of Muon Track -4 <𝜼_𝝁  < -2.5
-17.5 cm <𝑹_𝒂𝒃𝒔< 89.5 cm 
Rapidity of Muon Pair  -4.0 < 𝒚_𝝁𝝁 < -2.5
Pt of Muon Pair 𝑷_𝑻^𝝁𝝁<𝟎.𝟐𝟓 𝑮𝒆𝑽/𝑪
Distance of Closed Approached p× DCA criterion



#################Folder Discription############################
MCCode has mc analysis codes to submit the jobs on grid and collect simulated data
Directory starting output has the Analysis results.root
###################################
currently I am only working with 2018q data so it must be in 
output_2018q 
Readhistogram.py is main code
fitter.py has the fit function defined
functiontest.py is to test the fit function before implementing them on readhistogram.py
mccodetest.py is to test whethere the fit function fit to mc data properly


