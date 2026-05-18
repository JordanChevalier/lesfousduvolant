PORT=$(python -c "import random; print(random.randint(50000, 60000))")
echo "La compétition se passe sur 127.0.0.1:$PORT"
#uvx --from amazinggame killall

find . -name "*.log" -exec rm \{} \;

uvx --from amazinggame server -p $PORT --timeout 1 &

uvx --from amazinggame viewer -p $PORT &
# https://www.speedscope.app/
# py-spy record -o profile.data --format speedscope -- python -m amazinggame.viewer -p $PORT &
#uv run python -m amazinggame.viewer -p $PORT --small-window &
sleep 2

gcc -Wall -o lesfouduvolant.exe sample_player_client.c strategie.c #même ligne dans runtest.sh

./lesfouduvolant.exe 127.0.0.1 $PORT "LesFousDuVolant"

sleep 500
#uvx --from amazinggame killall
