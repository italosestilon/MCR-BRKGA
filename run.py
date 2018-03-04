import os

instances = [
	"instance-normal-10_10_9069566213990078274",
	"instance-normal-10_30_5101836430196424830",
	"instance-normal-10_50_1299250510484383223",
	"instance-normal-20_10_4353139248543192163",
	"instance-normal-20_30_8142950210851029772",
	"instance-normal-20_50_4342701307052564344",
	"instance-normal-30_10_1312402075301207550",
	"instance-normal-30_30_2156813194944348711",
	"instance-normal-30_50_8505631669847462694",
	"instance-normal-5_10_11189796138897731",
	"instance-normal-5_30_203679956587613087",
	"instance-normal-5_50_2272890002882406950",
	"instance-similar-10_10_4101995495510533711",
	"instance-similar-10_10_4484439307827160459",
	"instance-similar-10_30_8289865501567529889",
	"instance-similar-10_50_2990018272429598429",
	"instance-similar-20_10_1160072664559416098",
	"instance-similar-20_30_5754620931927865713",
	"instance-similar-20_50_5986155739858567165",
	"instance-similar-30_10_198943839508865483",
	"instance-similar-30_30_3109307287878925889",
	"instance-similar-30_50_7740251636409470100",
	"instance-similar-5_10_7700278471317325539",
	"instance-similar-5_30_541915693750959009",
	"instance-similar-5_50_3911772527774523819",
	"instance-uniform-10_10_7154584347338134297",
	"instance-uniform-10_30_1746359552420434941",
	"instance-uniform-10_50_5193192146419259819",
	"instance-uniform-20_10_8536110520078009685",
	"instance-uniform-20_30_6804260996746362198",
	"instance-uniform-20_50_3785576307725700678",
	"instance-uniform-30_10_5372368400714571683",
	"instance-uniform-30_30_1807058463452882016",
	"instance-uniform-30_50_7605177278520993555",
	"instance-uniform-5_10_8380045905751772194",
	"instance-uniform-5_30_4882940996471638670",
	"instance-uniform-5_50_7437980588482031995"
];

algorithms = [
	("brkgaAPI/src/samplecode", "brkga"),
	("branch_and_bound/main", "bb")
];

print ("make BB")
os.system("cd branch_and_bound && make")
os.system("cd ..")

print ("make brkga")
os.system("cd brkgaAPI/src && make")


for inst in instances:
	for (alg, path) in algorithms:
		print ("./%s instances/%s.txt > out/%s/%s.out" % (alg, inst, path, inst))
		os.system("./%s instances/%s.txt > out/%s/%s.out" % (alg, inst, path, inst))

	print ("java -jar MRC-gurobi.jar instances/%s.txt > out/pli/%s.out" % (inst, inst))
	os.system("java -jar MRC-gurobi.jar instances/%s.txt > out/pli/%s.out" % (inst, inst))

	print("")
