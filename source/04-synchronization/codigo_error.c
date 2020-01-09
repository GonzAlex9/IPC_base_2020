do {
	r = sem_wait(myem); //return -1 with errno=EINTR if interrupted
} while ((r==-1) && (errno=EINTR));
