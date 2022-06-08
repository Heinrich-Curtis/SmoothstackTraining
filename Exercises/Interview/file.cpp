namspace myutil
{
// Generates random secure auth key
std::string gen_sec_key()
{
...
}
class AuthKey
{
private:
std::string key_;
int accessCounter_;
};
} // namespace myutil
void main()
{
myutil::AuthKey k1;
const myutil::AuthKey k2( k1 );
std::cout << k2.getKey() << std::endl;
}
