function deltaEpsilon = calcDeltaEpsilon(y1U,y1T,y2U,y2T)
% Calculates delta Epsilon as by Eq. 9 of the paper

eU = calcEpsilon(y1U,y2U);
eT = calcEpsilon(y1T,y2T);

deltaEpsilon = (eT - eU)/(eT + eU);

function epsilon = calcEpsilon(y1,y2)

epsilon = sum(abs(y1-y2))/length(y1);