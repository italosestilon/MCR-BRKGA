import pickle
import math

instancias = [

	("instance-normal-5_10_1556037329065896909.txt", 5, 10, "normal"),
	("instance-normal-5_30_3915474638750880997.txt", 5, 30, "normal"),
	("instance-normal-5_50_5645167529901746724.txt", 5, 50, "normal"),
	("instance-normal-10_10_6528567610788970942.txt", 10, 10, "normal"),
	("instance-normal-10_30_400562113371764257.txt", 10, 30, "normal"),
	("instance-normal-10_50_8868171147548326926.txt", 10, 50, "normal"),
	("instance-normal-20_10_6328278962814994927.txt", 20, 10, "normal"),
	("instance-normal-20_30_8862008393618559334.txt", 20, 30, "normal"),
	("instance-normal-20_50_3638527140661504545.txt", 20, 50, "normal"),
	("instance-normal-30_10_5584669284027276941.txt", 30, 10, "normal"),
	("instance-normal-30_30_819562567068417602.txt", 30, 30, "normal"),
	("instance-normal-30_50_8495668216942044676.txt", 30, 50, "normal"),
	("instance-similar-5_10_211504906417112605.txt", 5, 10, "similar"),
	("instance-similar-5_30_8004114527165865034.txt", 5, 30, "similar"),
	("instance-similar-5_50_7285937797532987407.txt", 5, 50, "similar"),
	("instance-similar-10_10_1620148828828682729.txt", 10, 10, "similar"),
	("instance-similar-10_30_7340918304851233631.txt", 10, 30, "similar"),
	("instance-similar-10_50_1399345011251712154.txt", 10, 50, "similar"),
	("instance-similar-20_10_6246196465249217373.txt", 20, 10, "similar"),
	("instance-similar-20_30_7534284746474750159.txt", 20, 30, "similar"),
	("instance-similar-20_50_3590046920785578041.txt", 20, 50, "similar"),
	("instance-similar-30_10_4083237986323606591.txt", 30, 10, "similar"),
	("instance-similar-30_30_8100326382418160103.txt", 30, 30, "similar"),
	("instance-similar-30_50_1331763098226818453.txt", 30, 50, "similar"),
	("instance-uniform-5_10_8918558323521365203.txt", 5, 10, "uniform"),
	("instance-uniform-5_30_5316484456983232856.txt", 5, 30, "uniform"),
	("instance-uniform-5_50_3454365547511170571.txt", 5, 50, "uniform"),
	("instance-uniform-10_10_186296902021270023.txt", 10, 10, "uniform"),
	("instance-uniform-10_30_996401170637413420.txt", 10, 30, "uniform"),
	("instance-uniform-10_50_6620044706615721902.txt", 10, 50, "uniform"),
	("instance-uniform-20_10_8497498977251904170.txt", 20, 10, "uniform"),
	("instance-uniform-20_30_7946767810833159230.txt", 20, 30, "uniform"),
	("instance-uniform-20_50_7166791217815916714.txt", 20, 50, "uniform"),
	("instance-uniform-30_10_5487141185222699701.txt", 30, 10, "uniform"),
	("instance-uniform-30_30_5518634776187720274.txt", 30, 30, "uniform"),
	("instance-uniform-30_50_6897445488919758962.txt", 30, 50, "uniform")
]



with open('projects.tex', 'w') as texfile:
	texfile.write('\\begin{scriptsize}\n')
	texfile.write('\\setlength\\LTleft{0pt}            % default: \\fill\n')
	texfile.write('\\setlength\\LTright{0pt}           % default: \\fill\n')
	texfile.write('\\label{table:tests}\n')
	texfile.write('\\begin{longtable}{@{\\extracolsep{\\fill}}l|l|l|ll|lll|lll@{}}\n')


	texfile.write('\\hline\n')
	texfile.write('\\textbf{K} & \\textbf{Max set size} & \\textbf{Type} & \\textbf{BB} & & \\textbf{BRKGA} & & & \\textbf{ILP}\\\\ \n')
	texfile.write('\\hline\n')

	texfile.write('& & & incubent & time & incubent & variance & time & incubent & time & gap \\%\\\\ \n'); #& $incubent$ & time & $incubent$ & time
	texfile.write('\\hline\n')
	texfile.write('\\endfirsthead\n')

	texfile.write('\\hline\n')
	texfile.write('\\textbf{K} & \\textbf{Max set size} & \\textbf{Type} & \\textbf{BB} & & \\textbf{BRKGA} & & & \\textbf{ILP}\\\\ \n') #& brkga & PLI
	texfile.write('\\hline\n')
	texfile.write('& & & incubent & time & incubent & variance & time & incubent & time & gap \\%\\\\ \n'); #& $incubent$ & time & $incubent$ & time
	texfile.write('\\hline\n')
	texfile.write('\\endhead\n')
	texfile.write('\\hline \multicolumn{10}{r}{{Continue next page...}} \\\\ \n')
	texfile.write('\\endfoot\n')
	texfile.write('\\multicolumn{10}{r}{{}} \\\\ \n')
	texfile.write('\\endlastfoot\n')

	for inst in instancias:

		#texfile.write(' %s ' % ( inst ) )

		texfile.write(' %d & %d & %s' % (inst[1], inst[2], inst[3]))

		flag1 = True

		menor = 3600

		try:
			filename = "out/bb/%s.out" % (inst[0])
			f = open(filename)
			lines = f.readlines();
			r1   = int(lines[len(lines)-4].split(" ")[1])
			t1   = float(lines[len(lines)-2].split(" ")[1])
			sub1 = int(lines[len(lines)-3].split(" ")[1])
		except:
			flag1 = False


		if flag1:
			if t1 < menor:
				menor  = t1

		flag2 = True

		'''
		try:
			filename = "out/bb_brkga/%s.out" % (inst[0])
			f = open(filename)
			lines = f.readlines();
			r2   = int(lines[len(lines)-4].split(" ")[1])
			t2   = float(lines[len(lines)-2].split(" ")[1])
			sub2 = int(lines[len(lines)-3].split(" ")[1])
		except:
			flag2 = False

		if flag2:
			if t2 < menor:
				menor  = t2
		'''


		flag3 = True

		try:
			filename = "out/brkga/%s.out" % (inst[0])
			f = open(filename)
			lines = f.readlines();
			r3   = int(math.ceil(float(lines[len(lines)-2].split(" ")[1])))
			t3   = float(lines[len(lines)-1].split(" ")[1])
			var = 0
			for i in range(0, len(lines) - 2):
				xi = int(lines[i])
				var += (xi - r3)**2

			v3 = var/((len(lines)-2) * 1.0)
					
		except Exception as e: 
			print(e)
			flag3 = False

		razao1 = menor


		flag4 = True

		try:
			filename = "integer_programming/result/%s" % (inst[0])
			f = open(filename)
			lines = f.readlines();
			r4   = int(lines[0])
			filename = "integer_programming/time/%s" % (inst[0])
			f = open(filename)
			lines = f.readlines();
			t4   = float(lines[0])
			filename = "integer_programming/gap/%s" % (inst[0])
			f = open(filename)
			lines = f.readlines();
			g4 = float(lines[0])
		except:
			flag4 = False

		razao1 = menor

		if flag1:
			if t1 < 3600:
				texfile.write('& \\textbf{%d*}' % ( r1 ) )
			else:
				texfile.write('& %d' % ( r1 ) )

			if t1 >= 3600:
				texfile.write('& 3600s')
			elif t1 <= 100:
				texfile.write('& %.2fs' % ( t1 ) )
			else:
				texfile.write('& %ds ' % ( t1 ) )

		else:
			texfile.write('& fail & fail')
		'''
		if flag2:
			if t2 < 3600:
				texfile.write('& %d*' % ( r2 ) )
			else:
				texfile.write('& %d' % ( r2 ) )
			if t2 >= 3600:
				texfile.write('& 3600s')
			elif t2 <= 100:
				texfile.write('& %.2fs ' % ( t2 ) )
			else:
				texfile.write('& %ds ' % ( t2 ) )
		else:
			texfile.write('& fail & fail')
		'''

		if flag3:
			if r3 >= r1:
				texfile.write('& \\textbf{%d}' % ( r3 ))
			else:
				texfile.write('& %d' % ( r3 ) )

			texfile.write('& %.2f' % ( v3 ) )


			if t3 >= 3600:
				texfile.write('& 3600s')
			elif t3 <= 100:
				texfile.write('& %.2fs ' % ( t3 ) )
			else:
				texfile.write('& %ds ' % ( t3 ) )
		else:
			texfile.write('& fail & fail')


		if flag4:
			if t4 < 3600:
				texfile.write('& \\textbf{%d*}' % ( r4 ) )
			elif r4 >= r1 and r4 >= r3:
				texfile.write('& \\textbf{%d}' % ( r4 ) )
			else:
				texfile.write('& %d' % ( r4 ) )

			if t4 >= 3600:
				texfile.write('& 3600s')
			elif t4 <= 100:
				texfile.write('& %.2fs ' % ( t4 ) )
			else:
				texfile.write('& %ds ' % ( t4 ) )

			if g4 < 0:
				texfile.write('& -- ')
			elif g4 <= 100:
				texfile.write('& %.2f ' % ( g4 ) )
			else:
				texfile.write('& %d ' % ( g4 ) )
		else:
			texfile.write('& fail & fail')

		texfile.write('\\\\\n')



	texfile.write('\\hline \n')
	texfile.write('\\caption{Tests results}\\\\ \n')
	texfile.write('\\end{longtable}\n')
	texfile.write('\\end{scriptsize}\n')
