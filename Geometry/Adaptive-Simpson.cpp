    const double eps=1e-12; // represents how much precision you need
    double f(double x){ /* function for integration */}
    double simpson(double l,double r){return (r-l)/6*(f(l)+4*f((l+r)/2)+f(r));}
    double calc(double l,double r,double ans)
    {
    	double m=(l+r)/2,x=simpson(l,m),y=simpson(m,r);
    	if(abs(x+y-ans)<eps)return x+y;
    	return calc(l,m,x)+calc(m,r,y);
    }
    int main()
    {
        double L,R;
        scanf("%lf%lf",&L,&R);
        printf("%.8f\n",calc(L,R,simpson(L,R)));
    }
