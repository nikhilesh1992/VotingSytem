struct intpair {
        char candidateName[12];
        int voterID;
};

program VOTE_PROG {
        version VOTE_VERS {
                string VOTE_ZERO(void) = 1;
                string ADD_VOTER(intpair) = 2;
                string VOTE(intpair) = 3;
                string LIST(void) = 4;
                string VOTE_COUNT(intpair) = 5;
        } = 1;
} = 0x23451111;