## bitmask

- [Problem C. Dynamic Graph Matching](https://acm.hdu.edu.cn/showproblem.php?pid=6321)

dp, bitmask, update_dp


DP Optimization			
	Theory		
			http://wcipeg.com/wiki/Convex_hull_trick
			http://satanic0258.hatenablog.com/entry/2016/08/16/181331
			https://cp-algorithms.com/geometry/convex_hull_trick.html
			https://codeforces.com/blog/entry/8219
			https://codeforces.com/blog/entry/47932
			https://codeforces.com/blog/entry/60514
			https://codeforces.com/blog/entry/15296
			https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=3&ved=2ahUKEwiKh7GszvzdAhXDylMKHRzICAYQFjACegQIBxAC&url=http%3A%2F%2Fmaratona.ic.unicamp.br%2FMaratonaVerao2017%2Fdocuments%2Fdp.pdf&usg=AOvVaw3weMD53_xWJIn6hgwk7kbw
			https://peltorator.ru/posts/knuth_yao_optimization/
			https://blog.myungwoo.kr/98
			https://codeforces.com/blog/entry/8219
			https://robert1003.github.io/2020/02/29/dp-opt-knuth.html
			https://web.archive.org/web/20180611211409/http://apps.topcoder.com/forums/;jsessionid=A1FECFD4012E73C3F1D2E4C516387003?module=Thread&threadID=579321&start=0&mc=17#823126
			https://web.archive.org/web/20180920154800/http://apps.topcoder.com/forums/?module=Thread&threadID=697369&start=0&mc=22
			https://web.archive.org/web/20220128223052/http://chino.taipei/code-2016-0402Algorithm-DP優化之四邊形不等式優化/

			https://codeforces.com/blog/entry/82924 

			https://maratona.ic.unicamp.br/MaratonaVerao2017/documents/dp.pdf
			https://codeforces.com/blog/entry/47764


			https://codeforces.com/blog/entry/67664
			https://codeforces.com/blog/entry/50036

			https://sam571128.codes/2021/10/23/Slope-Trick/
			https://koosaga.com/243
			https://codeforces.com/blog/entry/123211
			https://codeforces.com/blog/entry/47821
			https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0904_abc217
			https://koosaga.com/243



	Problems		
	https://atcoder.jp/contests/arc123/editorial
	https://atcoder.jp/contests/abc217/tasks/abc217_h
	https://www.cnblogs.com/zltzlt-blog/p/17566846.html
	https://atcoder.jp/contests/abc228/editorial/2960
			https://vjudge.net/contest/225800
			https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14/editorial

			https://codeforces.com/contest/1278/problem/D ??


专题12 基础DP								
								
		Origin	Title	Solved	Source	Note		
	1	HDU-1024	Max Sum Plus Plus	13052				
	2	HDU-1029	Ignatius and the Princess IV	21227				
	3	HDU-1069	Monkey and Banana	11717	University of Ulm Local Contest 1996			
	4	HDU-1074	Doing Homework	6357				
	5	HDU-1087	Super Jumping! Jumping! Jumping!	23897				
	6	HDU-1114	Piggy-Bank	18210	Central Europe 1999			
	7	HDU-1176	免费馅饼	20844				
	8	HDU-1260	Tickets	6219	浙江工业大学第四届大学生程序设计竞赛			
	9	HDU-1257	最少拦截系统	25369	浙江工业大学第四届大学生程序设计竞赛			
	10	HDU-1160	FatMouse's Speed	9218	Zhejiang University Training Contest 2001			
	11	POJ-1015	Jury Compromise	6919	Southwestern European Regional Contest 1996			
	12	POJ-1458	Common Subsequence	25787	Southeastern Europe 2003			
	13	POJ-1661	Help Jimmy	4850	POJ Monthly--2004.05.15 CEOI 2000			
	14	POJ-2533	Longest Ordered Subsequence	23968	Northeastern Europe 2002, Far-Eastern Subregion			
	15	POJ-3186	Treats for the Cows	4732	USACO 2006 February Gold & Silver			
	16	HDU-1078	FatMouse and Cheese	7108	Zhejiang University Training Contest 2001			
	17	HDU-2859	Phalanx	2315	2009 Multi-University Training Contest 5 - Host by NUDT			
	18	POJ-3616	Milking Time	8034	USACO 2007 November Silver			
	19	POJ-3666	Making the Grade	4917	USACO 2008 February Gold			
								
								
								
								
digit dp								
								
		Origin	Title	Solved	Source	Note		
	1	CodeForces-55D	Beautiful numbers	5119	Codeforces Beta Round 51			
	2	HDU-4352	XHXJ's LIS	1966	2012 Multi-University Training Contest 6			
	3	HDU-2089	不要62	25609	迎接新学期――超级Easy版热身赛			
	4	HDU-3555	Bomb	8046	2010 ACM-ICPC Multi-University Training Contest（12）――Host by WHU			
	5	POJ-3252	Round Numbers	6690	USACO 2006 November Silver			
	6	HDU-3709	Balanced Number	3593	2010 Asia Chengdu Regional Contest			
	7	HDU-3652	B-number	5397	2010 Asia Regional Chengdu Site ―― Online Contest			
	8	HDU-4734	F(x)	4029	2013 ACM/ICPC Asia Regional Chengdu Online			
	9	ZOJ-3494	BCD Code	1308				
	10	HDU-4507	吉哥系列故事――恨7不成妻	2358	2013腾讯编程马拉松初赛第一场（3月21日）			
	11	SPOJ-BALNUM	Balanced Numbers	1276	Cuban Olympiad in Informatics 2012 - Day 2 Problem A			
								
								
Topic 20 Slope DP								
								
	Origin	Title	Solved	Source	Note			
	1	HDU-3507	Print Article	4308	2010 ACM-ICPC Multi-University Training Contest（7）――Host by HIT			
	2	HDU-2829	Lawrence	1910	2009 Multi-University Training Contest 2 - Host by TJU			
	3	HDU-4528	小明系列故事――捉迷藏	646	2013腾讯编程马拉松初赛第五场（3月25日）			
	4	HDU-1300	Pearls	1687	Northwestern Europe 2002			
	5	HDU-2993	MAX Average Problem	1005	2009 Multi-University Training Contest 19 - Host by BNU			
	6	UVALive-5097	Cross the Wall	189	Regionals 2010 >> Asia - Harbin			
	7	HDU-3045	Picnic Cows	913	2009 Multi-University Training Contest 14 - Host by ZJNU			
	8	HDU-3516	Tree Construction	1026	2010 ACM-ICPC Multi-University Training Contest（8）――Host by ECNU			
	9	POJ-1160	Post Office	8214	IOI 2000			
	10	POJ-1180	Batch Scheduling	1786	IOI 2002			
	11	POJ-2018	Best Cow Fences	4269	USACO 2003 March Green			
	12	POJ-3709	K-Anonymous Sequence	1526	POJ Founder Monthly Contest – 2008.12.28, Rainer			
	13	POJ-2841	Navigation Game	76	POJ Monthly--2006.06.25, Yang Yi			
	14	POJ-1260	Pearls	4900	Northwestern Europe 2002			
	15	UVA-12594	Naming Babies	126				
	16	HDU-3480	Division	1593	2010 ACM-ICPC Multi-University Training Contest（5）――Host by BJTU			
	17	UVALive-6771	Buffed Buffet	29	World Finals >> 2014 - Ekaterinburg			
								
								
Topic 21 Interval DP								
								
	Origin	Title	Solved	Source	Note			
	1	ZOJ-3537	Cake	1537				
	2	LightOJ-1422	Halloween Costumes	3011				
	3	POJ-2955	Brackets	8353	Stanford Local 2004			
	4	CodeForces-149D	Coloring Brackets	4013	Codeforces Round 106 (Div. 2)			
	5	POJ-1651	Multiplication Puzzle	8724	Northeastern Europe 2001, Far-Eastern Subregion			
	6	ZOJ-3469	Food Delivery	2143				
	7	HDU-4283	You Are the One	3449	2012 ACM/ICPC Asia Regional Tianjin Online			
	8	HDU-2476	String painter	3497	2008 Asia Regional Chengdu			
								
								
Feature 32 Plug DP								
	Origin	Title	Solved	Source	Note			
	1	HDU-1693	Eat the Trees	1829	2008 “Sunline Cup” National Invitational Contest			
	2	URAL-1519	Formula 1	1531	Timus Top Coders: Third Challenge			
	3	FZU-1977	Pandora adventure	103	The 35th ACM/ICPC Asia Regional Fuzhou Site —— Online Contest			
	4	HDU-1964	Pipes	407	NWERC2004			
	5	HDU-3377	Plan	353	HDOJ Monthly Contest �C 2010.04.04			
	6	POJ-1739	Tony's Tour	1050	LouTiancheng@POJ			
	7	POJ-3133	Manhattan Wiring	706	Japan 2006			
	8	ZOJ-3466	The Hive II	267				
	9	ZOJ-3256	Tour in the Castle	422				
	10	ZOJ-3213	Beautiful Meadow	825				
	11	HDU-4285	circuits	244	2012 ACM/ICPC Asia Regional Tianjin Online			



bitmask pro 
	
- flood bitmask

	1. https://atcoder.jp/contests/arc160/tasks/arc160_f

	problema: tienes todas las permutaciones de los elementos 1, 2, ..., n. En cada paso puedes "ordenar" dos elementos (un par (xi, yi) y ordenas los elementos en esas dos posiciones). Debes responder cuantas permutaciones se van ordenando en cada paso.

	principal idea: 

	la idea es ir desvelando cada permutacion, de tal forma que al inicio no conozco como estan puestos los elementos, y en cada paso voy desvelando la ubicacion del elemento menor no desvelado, puedo darme cuenta que toda la permutacion se puede ver como ir prendiendo un bit en cada paso, o sea, un camino en un array n-dimensional 2^n. 

	lo otro importante que observar, es que al hacer esa simplificacion, solo me interesa como interactuan los 0s y 1s, y ellos interactuan igual, el que tiene 1 va primero y luego el de 0. Asi, en la k-esima operacion, lo que debo es considerar los k primeros cambios en cada mascara de bits y contar cuantos caminos "ordenados" hay entre el 0...000 y el 11.1111.


	secondary idea:

	lo importante es ver que si un par es aplicable y se puede aplicar en al menos una permutacion, entonces solo se pueden aplicar n^2/2 swaps, o sea, puede ocurrir dos cosas, que ese swap no cree mas swaps asi que reduce en 1, o que cree mas swaps en alguna permutacion, entonces por cada par que cree, solo se da si otro swap se cancela.

	2. https://www.luogu.com.cn/problem/P10813?contestId=184989

	idea: similar para el caso anterior solo que en cada paso agrego un subconjunto de 1s, aplico solo una vez todas las operaciones, y al momento de juntar, aplico dp sos, de tal forma que en cada vez que aplico puedo verlo como tener i elementos distintos.

