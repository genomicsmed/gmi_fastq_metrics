1) how do you run GMIFastQMetrics?

 

./gmi_fastq_metrics SRR1517991_1.fastq .

 

i) compile the file

 

g++ gmi_fastq_metrics.cpp -o gmi_fastq_metrics

 

ii) command? how to input the fastq? by directories?

 

./gmi_fastq_metrics input.fastq output_folder

Ex.

./gmi_fastq_metrics SRR1517991_1.fastq .

 

 

ii) output? it seems there's 4 outputs, is it 4 files per execution

 

Read Size: 76
Total Sum of Phred Scores: 6183986569
Total number of Q30 Bases with phred quality score higher or equal than 30: 155503406
Total number of Bases: 176179552
Total number of Reads with phred quality score higher or equal than 30: 2024564
Total number of Reads: 2318152
Max per base N content: 0.223540,0.016090,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000216,0.000000,0.000000,0.000000,0.000129,0.000000,0.000129,0.000820,0.004098,0.005306,0.008455,0.000216,0.003537,0.007420,0.005263,0.006514,0.001941,0.001165,0.004314,0.003624,0.002114,0.011863,0.011863,0.000302,0.009879,0.002373,0.011777,0.000388,0.017385,0.009361,0.006255,0.008153,0.004314,0.023294,0.002933,0.004659,0.004529,0.000431,0.000000,0.000647,0.000043,0.002200,0.005694
------------------ Summary ------------------
Percentage of bases with phred quality score higher or equal than 30: 88.264160
Percentage of reads with phred quality score higher or equal than 30: 87.335258
Average per base quality Score: 35.100479
Average per read quality Score: 34.612175

Time Taken: 1.056766
