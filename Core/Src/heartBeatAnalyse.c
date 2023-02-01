int prevNbBat=0;

int compteurBpm(int nbBat){
	int nbBpm = 0;

	//if the heart rate increases by 20 beats in 10 minutes then
	//there has been a problem with the ECG recording.
	if ((prevNbBat != 0) && (nbBat*6 > prevNbBat*6 + 20)) {
		printf("Problem during the recording\n");
		//We keep the old value
	}
	else {
		prevNbBat = nbBat;
	}
	nbBpm = prevNbBat*6;//extrapolation of beats/10sec to beats/min
	printf("bpm : %d\n",nbBpm);

	return nbBpm;
}
