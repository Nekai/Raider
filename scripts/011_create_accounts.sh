#!/bin/bash
#
# Create user accounts.
# Mostly mimicking Raider (except for Chuck and Lev's UIDs).

# Pull in config settings... not really needed for this script, but ordnung!
source $(dirname "$BASH_SOURCE")/000_config.sh

# Cloudinit has shared homes under /shared/home as opposed to usual /home.
# Change useradd default to create our users under shared one!
HOME_BASE=/shared/home
[[ -d $HOME_BASE ]] || mkdir -p $HOME_BASE
useradd -D -b $HOME_BASE 	# Keep! 051_rcac_scratch.sh relies on this

# HHS
useradd -u 1010 -g users -G wheel -c "Chuck Schwarz" -p '$6$Db6M1nOH3bdT3fbu$GGbeO0eYSS7p6xMf21lIsjtqwD1pMzqxmyFVdtzJo6mQtpd5FrQ8FhyXDl24y46iNHKvNOcnvKcJL8oCQz352.' chuck
useradd -u 1011 -g users -G wheel -c "Lev Gorenstein"   -p '$6$3.fHvkWXMVqm7JzP$20kNcI7cZHLaQu8/waPbo9NqiI3iAqiXtD4m.Za6/13Jogd7lmWr8GuNaCiljZNtx199ZI1q4dJzYwlVeIFqq0' lev
useradd -u 1012 -g users -c "Jeremy Meyer"     -p '$6$K5n/ABCN1OLeUulD$gvtFKmVQrXryU2WRThyu189hu82i9gHM.kJhBaFtMZgPaLIMYtgnSthrn9w.egXbTOEx/HBPVCSYAOdGoDo3e/'  jmeye90
useradd -u 1013 -g users -c "Nick Nolte"       -p '$6$rHvJEV8cRsjY7DPx$2sH0T5KsnbPlVkxciCUvvSisvoT/lY2NwVUy/Oaw80lot3EEeYFrtWDA.Z7BmPWmYeugSZZPQhxGBanA7BT8h.'  budtomazi
useradd -u 1014 -g users -G wheel -c "Jacob Sharp"      -p '$6$p06BdgV7zkYyhRMW$tPxLJgZk3mSn5WaVdxCYlgvUc3iDNlowkfnZxRcoP.mz76uJVWgfaf7Jl8L650OrJ4E/EjLgQlAjK6/FcAzEI0'  sharp67
useradd -u 1015 -g users -G wheel -c "Callum Gundlach"  -p '$6$v2WfT1wDJj7.4hIt$X56n82OH0QEKOW76xthGRjE8Qw/h/NMDDCg3eUR5LAhcfe.TwHC4fuXa00BYKlMPJ1TQ1zPjkMQyIjykZ4R2z1'  cgundlach
useradd -u 1016 -g users -c "Chris Page"       -p '$6$QTsnrEKlj6.SIbHC$AOxgWnsV4LFoF0WHJEWsLcwd15z9xvQ8vynYJ57cpgzzBUmkpmLJsnU56oY6eqUaojSPaWAjoXhIQbtRsOD2B/'  cpage19
useradd -u 1017 -g users -G wheel -c "Patrick Finnegan" -p '$6$0OJ49TG3$bHcpsVTQVgEKW1q7ORv5IR1xrhNTtSHqvJjg9lFHsYdhHngyRA.m5iUgUYFLHKpNvr2De2jFF/2LARJFAArTc/' finnegpt
useradd -u 1018 -g users -c "Nick Frooninckx"  -p '$6$kc27N/WE.OTPBM4a$5s/RJrSpQ1Jm6rrBt3OQRLy3UxNFWaW72urXxO65KJrTKUwlMQFxI/yBieN4Es3kgByIdlQq7dvlkMZjDufZi1' leghost
useradd -u 1019 -g users -c "Eduardo Wedekind" -p '$6$xwQrHT2c$a3ZK3JBGjI8RV3riCFdyPnzLSuaSnIJLfaq46/awgAnBVkBToUy4xcwYjnMaLy3Z0j4/NiZuC9CrQWs9g8NEI.' eduardo
useradd -u 1020 -g users -c "Caitlin Hillery"  -p '$6$hQ2P5mqB$Z2sSl3/AJk9bMbaWbBSjwy1NjKeczqjuZaGBCh7lmGkcukZyTPpQgrVlxzEAhwFROCWWseYjltPI4ikrxbkdW0' caitlin


# Purdue students
useradd -u 1002 -g users  -c "Brandon Stewart"   -p '$6$5bUcs1.xNqOPARMZ$QHITxe5jGRCbIEVfAK81qnhtvIagbi99NmSZxRngrQKLyTdFC7jG4BES5uaZJtNVqqd4CYR8GtnSvX0cVy/B41' stewart
useradd -u 1003 -g users -c "Austyn Cousins"    -p '$6$eK1ctmHkISlfnOZR$sz47opQycJoi/YKkAlrbInZdQ91sigc2smg6vwlFBE9buYqZ3DYKprp9Sk7CTfQZEQD5y.LrArI07mXI32.Vd0' acousin
useradd -u 1004 -g users -c "Austin Horning"    -p '$6$CH97l36uxfGmnq02$fj2CctHkIeQ1Pl71ZM/ElrcoPYvgsfgvwQkaOnGsglu67LWh2tssAooJUCjF4.Ax8CXNtchHAehbd92b6.RqQ.' ahornin
