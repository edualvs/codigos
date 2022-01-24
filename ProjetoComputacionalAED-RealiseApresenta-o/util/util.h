int pega_ip(string ip) {
    string final;
    for (int i=10; i <= ip.size(); i++) {
        final= final + ip[i];
    }
    return stoi(final);
}
