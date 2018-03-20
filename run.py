import os

instances = [
	"instance-normal-10_10_6528567610788970942.txt",
	"instance-normal-10_30_400562113371764257.txt",
	"instance-normal-10_50_8868171147548326926.txt",
	"instance-normal-20_10_6328278962814994927.txt",
	"instance-normal-20_30_8862008393618559334.txt",
	"instance-normal-20_50_3638527140661504545.txt",
	"instance-normal-30_10_5584669284027276941.txt",
	"instance-normal-30_30_819562567068417602.txt",
	"instance-normal-30_50_8495668216942044676.txt",
	"instance-normal-5_10_1556037329065896909.txt",
	"instance-normal-5_30_3915474638750880997.txt",
	"instance-normal-5_50_5645167529901746724.txt",
	"instance-similar-10_10_1620148828828682729.txt",
	"instance-similar-10_30_7340918304851233631.txt",
	"instance-similar-10_50_1399345011251712154.txt",
	"instance-similar-20_10_6246196465249217373.txt",
	"instance-similar-20_30_7534284746474750159.txt",
	"instance-similar-20_50_3590046920785578041.txt",
	"instance-similar-30_10_4083237986323606591.txt",
	"instance-similar-30_30_8100326382418160103.txt",
	"instance-similar-30_50_1331763098226818453.txt",
	"instance-similar-5_10_211504906417112605.txt",
	"instance-similar-5_30_8004114527165865034.txt",
	"instance-similar-5_50_7285937797532987407.txt",
	"instance-uniform-10_10_186296902021270023.txt",
	"instance-uniform-10_30_996401170637413420.txt",
	"instance-uniform-10_50_6620044706615721902.txt",
	"instance-uniform-20_10_8497498977251904170.txt",
	"instance-uniform-20_30_7946767810833159230.txt",
	"instance-uniform-20_50_7166791217815916714.txt",
	"instance-uniform-30_10_5487141185222699701.txt",
	"instance-uniform-30_30_5518634776187720274.txt",
	"instance-uniform-30_50_6897445488919758962.txt",
	"instance-uniform-5_10_8918558323521365203.txt",
	"instance-uniform-5_30_5316484456983232856.txt",
	"instance-uniform-5_50_3454365547511170571.txt"

];

os.system("cd BB && mkdir -p solutions")
os.system("cd BB2 && mkdir -p solutions")
os.system("cd brkgaAPI && mkdir -p solutions")

os.system("mkdir -p out")
os.system("cd out && mkdir -p brkga")
os.system("cd out && mkdir -p bb")
os.system("cd out && mkdir -p bb_brkga")
os.system("cd out && mkdir -p pli")


for inst in instances:
	print ("brkga %s" % (inst))
	os.system("./brkgaAPI/src/samplecode instances/%s > out/brkga/%s.out" % (inst, inst))

	#print ("BB %s" % (inst))
	#os.system("./BB/main instances/%s > out/bb/%s.out" % (inst, inst))

	#print ("BB-brkga %s" % (inst))
	#os.system("./BB2/main instances/%s brkgaAPI/solutions/%s > out/bb_brkga/%s.out" % (inst, inst, inst))

	print("")
