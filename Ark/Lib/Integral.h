#ifndef _ARK_INTEGRAL_H
#define _ARK_INTEGRAL_H
double VectorDot(const double *const first,const double *const second)
{
	double sum = 0;
	for(int j = 0;j < Q;++j)
		sum += first[j]*second[j];
	return sum;
}
double VectorDot(const double *const first)
{
	double sum = 0;
	for(int j = 0;j < Q;++j)
		sum += first[j];
	return sum;
}
#endif