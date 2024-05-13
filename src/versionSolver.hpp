#include<string>

enum class SolverVersion {
    KpSolverDPv0,
    KpSolverDPv1,
    KpSolverDPv1bis,
    KpSolverDPv2,
    KpSolverDPv3
};

SolverVersion& operator++(SolverVersion& version) {
    version = static_cast<SolverVersion>(static_cast<int>(version) + 1);
    if (version == SolverVersion::KpSolverDPv3 ) {
        version = static_cast<SolverVersion>(0);
    }
    return version;
}


std::string toStringSolver(SolverVersion _type){
    std::string s("");
        switch(_type){
        case SolverVersion::KpSolverDPv0:
            s= "KpSolverDPv0"; break;
        case SolverVersion::KpSolverDPv1 :
            s= "KpSolverDPv1";break;
        case SolverVersion::KpSolverDPv1bis:
            s= "KpSolverDPv1bis"; break;
        case SolverVersion::KpSolverDPv2 :
            s= "KpSolverDPv2";
        case SolverVersion::KpSolverDPv3:
            break;
    }
     return s;
}
