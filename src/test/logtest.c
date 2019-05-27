#include <stdio.h>
#include <util/log.h>

int TST_Log()
{
        log_msg("This is a %s Message", "simple");
        log_err("This is an Error");
        log_dbg("This is a Debug Message");
        log_wrn("This is a Warning");
        return 1;
}

int main()
{
        TST_Log();

        return 0;
}
