#!/bin/bash
LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH ./bin/ama_test --log-to-console --cfg-name ./etc/ama.json  --data-to-console --data-to-csv --data-to-latency \
    --snapshot --index-snapshot --tick-order --tick-execution --option-snapshot \
    --hk-snapshot --csiindex-snapshot --afterhour-fixedprice-snapshot \
    --afterhour-fixedprice-tick-execution --future-snapshot --orderqueue --neeq-snapshot --order-book


