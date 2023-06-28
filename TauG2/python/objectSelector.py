class ObjectSelector:
    def __init__(self, _year = "None" ):
        self.year = _year


class GenParticleSelector(ObjectSelector):
    def __init__(self, _year = "None" ):
        self.year = _year

    def evalGenParticle(self, genp):
        return True
        

class ElectronSelector(ObjectSelector):
    def __init__(self, _minPt = 10):
        self.minPt = _minPt

    def evalElectron(self, el):
        isEBEE = True if abs(el.eta)>1.4442 and abs(el.eta)<1.5660 else False
        if isEBEE: return False       
        if el.pt < self.minPt: return False
        if abs(el.eta) > 2.5: return False
        if not el.mvaFall17V2Iso_WPL: return False
	##if el.miniPFRelIso_all>0.50: return False
        ##if abs(el.dxy) > 0.05 or abs(el.dz) > 0.2: return False

        return True

class TauSelector(ObjectSelector):
    def __init__(self, _minPt = 24):
        self.minPt = _minPt

    def evalTau(self, tau):
        if tau.pt < self.minPt: return False
        if abs(tau.eta) > 2.3: return False
        #if abs(tau.dz) > 0.2: return False
        if tau.decayMode not in [0,1,10,11]: return False
	#if not tau.idDecayModeNewDMs: return False
	#if tau.decayMode==5: return False
        #if tau.decayMode==6: return False
        if abs(tau.charge)!=1: return False
        if tau.idDeepTau2017v2p1VSe<3: return False # VVLoose
        if tau.idDeepTau2017v2p1VSmu<1: return False # VLoose
        if tau.idDeepTau2017v2p1VSjet<1: return False # VVVLoose

        return True
        
class MuonSelector(ObjectSelector):
    def __init__(self, minPt = 10, ID = 'medium'):
        self.minPt = minPt
        self.id = ID

    def evalMuon(self, mu):
        if mu.pt < self.minPt: return False
        if abs(mu.eta) > 2.4: return False
        if mu.pfRelIso04_all>0.5: return False # was 0.5
        #if abs(mu.dxybs) > 0.05 or abs(mu.dz) > 1.0: return False
        if self.id == 'tight' and not mu.tightId: return False
        elif self.id == 'medium' and not mu.mediumId: return False
        elif self.id == 'loose' and not mu.looseId: return False
	      
        return True

