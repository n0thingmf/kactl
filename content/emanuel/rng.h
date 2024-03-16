mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());

long long random(long long l, long long r){
   return uniform_int_distribution<long long>(l,r)(rng);
}
