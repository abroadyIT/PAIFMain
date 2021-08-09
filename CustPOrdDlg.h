#pragma once

#include "..\PAIFLibs\AfxErrorLib.h"
#include "..\PAIFLibs\AfxCntrlLib.h"
#include "PAIFMainLib.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"

#include "PickDlg.h"

// CCustPOrd dialog

//
// RULES:
//
// MSET
// *******************************************************************************
// POrdPQ
// POrdPQ()	= MSet.POrdPQ + m_PAdjPQ + sum(PSet.PAdjPQ)
// PRemPQ	= POrdPQ() - F.DScnPQ - F.DShpPQ

//
// PSet
// *******************************************************************************
// PPrmPQ()	= PSet.PPrmPQ + PSet.PAdjPQ

class CCustPOrdMSetPSetPAdj
{
public:
	typedef enum tagDBOp {
		DB_NULLOP			= 0,
		DB_ADJQTY			= 1,
		DB_SETQTY			= 2
	} DBOP, * LPDBOP;

	CCustPOrdMSetPSetPAdj() : m_PKNo(0), m_DBOp(DB_NULLOP)
	{
		PrmdDT = SqlNull;
		PAdjPQ = (double)0.0;
	}
	CCustPOrdMSetPSetPAdj(const size_t& PKNo, const SqlDateTime& _AdjDT, const SqlNumeric<9, 2>& _AdjPQ) : m_PKNo(PKNo), m_DBOp(DB_ADJQTY)
	{
		PrmdDT = _AdjDT;
		PAdjPQ = (double)0.0;
		PAdjPQ = _AdjPQ;
	}
	~CCustPOrdMSetPSetPAdj()
	{
	}

	const CCustPOrdMSetPSetPAdj& operator=(const CCustPOrdMSetPSetPAdj& PAdj)
	{
		PrmdDT = PAdj.PrmdDT;
		PAdjPQ = PAdj.PAdjPQ;
		CmntSZ = PAdj.CmntSZ;

		m_PKNo = PAdj.m_PKNo;
		m_DBOp = PAdj.m_DBOp;
	}
	void DoMove(SqlNumeric<9, 2>& _AdjPQ)
	{
		PAdjPQ = (double)PAdjPQ + (double)_AdjPQ;
		m_DBOp = CCustPOrdMSetPSetPAdj::DB_ADJQTY;
	}
	void UnMove()
	{
		PAdjPQ = (double)0.0;
		m_DBOp = CCustPOrdMSetPSetPAdj::DB_NULLOP;
	}
	void DoEdit(SqlNumeric<9, 2>& _AdjPQ)
	{
		PAdjPQ = (double)PAdjPQ + (double)_AdjPQ;
		m_DBOp = CCustPOrdMSetPSetPAdj::DB_ADJQTY;
	}
	void UnEdit()
	{
		PAdjPQ = (double)0.0;
		m_DBOp = CCustPOrdMSetPSetPAdj::DB_NULLOP;
	}

	SqlDateTime						PrmdDT;
	SqlNumeric<9, 2>				PAdjPQ;
	SqlVarChar<255>					CmntSZ;
	size_t							m_PKNo;
	DBOP							m_DBOp;
};

class CCustPOrdMSetPSetPAdjTraits : public CElementTraits< CCustPOrdMSetPSetPAdj >
{
public:
	static bool CompareElements(CCustPOrdMSetPSetPAdj& ele1, CCustPOrdMSetPSetPAdj& ele2)
	{
		return (SqlDateTimeTraits::CompareElements(ele1.PrmdDT, ele2.PrmdDT));
	}
	static int CompareElementsOrdered(CCustPOrdMSetPSetPAdj& ele1, CCustPOrdMSetPSetPAdj& ele2)
	{
		return (SqlDateTimeTraits::CompareElementsOrdered(ele1.PrmdDT, ele2.PrmdDT));
	}
};

class CCustPOrdMSetPSetPAdjs : public CAtlList< CCustPOrdMSetPSetPAdj, CCustPOrdMSetPSetPAdjTraits >
{
public:
	CCustPOrdMSetPSetPAdjs()
	{
	}
	CCustPOrdMSetPSetPAdjs(const CCustPOrdMSetPSetPAdjs& PAdjs)
	{
		Copy(PAdjs);
	}
	void Free()
	{
		if (GetCount() > 0)
		{
			RemoveAll();
		}
	}
	void Copy(const CCustPOrdMSetPSetPAdjs& PAdjs)
	{
		if (&PAdjs == this)
		{
			return;
		}

		Free();
		
		if (PAdjs.GetCount() > 0)
		{
			AddTailList(&PAdjs);
		}
	}
	const CCustPOrdMSetPSetPAdjs& operator=(const CCustPOrdMSetPSetPAdjs& PAdjs)
	{
		Copy(PAdjs);

		return (static_cast<const CCustPOrdMSetPSetPAdjs&>(*this));
	}
};

class CCustPOrdMSetPSet : public CUSTPORDMSETPSET
{
public:
	typedef enum tagDBOp {
		DB_NULLOP			= 0,
		DB_INSERT			= 1,
		DB_EXISTS			= 2,
		DB_UPDATE			= 4,
		DB_DELETE			= 8
	} DBOP, * LPDBOP;

	CCustPOrdMSetPSet() : m_DBOp(DB_NULLOP)
	{
	}
	CCustPOrdMSetPSet(const size_t& PKNo, const CUSTPORDMSETPSET& PSet) : m_PKNo(PKNo), m_Orig(0), m_DBOp(DB_EXISTS)
	{
		CustID = PSet.CustID;
		MatlID = PSet.MatlID;
		POrdCT = PSet.POrdCT;
		POrdPQ = PSet.POrdPQ;
		POrdSQ = PSet.POrdSQ;
		PPrmPQ = PSet.PPrmPQ;
		PPrmSQ = PSet.PPrmSQ;
		F.CustPO = PSet.F.CustPO;
		F.PrmdIX = PSet.F.PrmdIX;
		F.PrmdDT = PSet.F.PrmdDT;
		F.OpndDT = PSet.F.OpndDT;
		F.IsOrig = PSet.F.IsOrig;
		F.Active = PSet.F.Active;
		F.UOrgCT = PSet.F.UOrgCT;
		F.POrgPQ = PSet.F.POrgPQ;
		F.POrgSQ = PSet.F.POrgSQ;
		F.UPrmCT = PSet.F.UPrmCT;
		F.PPrmPQ = PSet.F.PPrmPQ;
		F.PPrmSQ = PSet.F.PPrmSQ;
		F.PUsePQ = PSet.F.PUsePQ;
		F.PUseSQ = PSet.F.PUseSQ;
		F.UScnCT = PSet.F.UScnCT;
		F.DScnPQ = PSet.F.DScnPQ;
		F.DScnSQ = PSet.F.DScnSQ;
		F.UShpCT = PSet.F.UShpCT;
		F.DShpPQ = PSet.F.DShpPQ;
		F.DShpSQ = PSet.F.DShpSQ;
		F.StatID = PSet.F.StatID;
	}
	~CCustPOrdMSetPSet()
	{
	}
	void Dump(LPCTSTR th)
	{
		TCHAR		tz[256];	memset(tz, 0, sizeof(tz));

		AfxTrace(_T("%s\n"), th);

		_stprintf_s<_countof(tz)>(
			tz, 
			_T("-PSet:  pk=%02d dt=%04d/%02d/%02d pa=%.0f fp=%.0f\n"),
			m_PKNo,
			((F.PrmdDT == SqlNull) ? 0 : F.PrmdDT.Value.year),
			((F.PrmdDT == SqlNull) ? 0 : F.PrmdDT.Value.month),
			((F.PrmdDT == SqlNull) ? 0 : F.PrmdDT.Value.day),
			PAdjPQ(),
			FPrmPQ()
		);
		AfxTrace(tz);

		for (POSITION x = m_PAdjs.GetHeadPosition(); x != NULL; m_PAdjs.GetNext(x))
		{
			CCustPOrdMSetPSetPAdj&	pa = m_PAdjs.GetAt(x);

			_stprintf_s<_countof(tz)>(
				tz,
				_T(" -PAdj: pk=%02d dt=%04d/%02d/%02d pa=%.0f\n"),
				m_PKNo,
				((pa.PrmdDT == SqlNull) ? 0 : pa.PrmdDT.Value.year),
				((pa.PrmdDT == SqlNull) ? 0 : pa.PrmdDT.Value.month),
				((pa.PrmdDT == SqlNull) ? 0 : pa.PrmdDT.Value.day),
				(double)pa.PAdjPQ
			);
			AfxTrace(tz);
		}
	}
	const CCustPOrdMSetPSet& operator=(const CCustPOrdMSetPSet& PSet)
	{
		CustID = PSet.CustID;
		MatlID = PSet.MatlID;
		POrdCT = PSet.POrdCT;
		POrdPQ = PSet.POrdPQ;
		POrdSQ = PSet.POrdSQ;
		PPrmPQ = PSet.PPrmPQ;
		PPrmSQ = PSet.PPrmSQ;
		F.CustPO = PSet.F.CustPO;
		F.PrmdIX = PSet.F.PrmdIX;
		F.PrmdDT = PSet.F.PrmdDT;
		F.OpndDT = PSet.F.OpndDT;
		F.IsOrig = PSet.F.IsOrig;
		F.Active = PSet.F.Active;
		F.UOrgCT = PSet.F.UOrgCT;
		F.POrgPQ = PSet.F.POrgPQ;
		F.POrgSQ = PSet.F.POrgSQ;
		F.UPrmCT = PSet.F.UPrmCT;
		F.PPrmPQ = PSet.F.PPrmPQ;
		F.PPrmSQ = PSet.F.PPrmSQ;
		F.PUsePQ = PSet.F.PUsePQ;
		F.PUseSQ = PSet.F.PUseSQ;
		F.UScnCT = PSet.F.UScnCT;
		F.DScnPQ = PSet.F.DScnPQ;
		F.DScnSQ = PSet.F.DScnSQ;
		F.UShpCT = PSet.F.UShpCT;
		F.DShpPQ = PSet.F.DShpPQ;
		F.DShpSQ = PSet.F.DShpSQ;
		F.StatID = PSet.F.StatID;

		m_PAdjs = PSet.m_PAdjs;
		m_PKNo = PSet.m_PKNo;
		m_Orig = PSet.m_Orig;
		m_DBOp = PSet.m_DBOp;

		return (static_cast<const CCustPOrdMSetPSet&>(*this));
	}
	// Status
	double PAdjPQ()
	{
		double	pq	= 0.0;
		double	mo	= 0.0;

		for (POSITION x = m_PAdjs.GetHeadPosition(); x != NULL; m_PAdjs.GetNext(x))
		{
			pq = pq + (double)m_PAdjs.GetAt(x).PAdjPQ;
		}
		mo = fmod(pq, 1.0);
		pq = ((mo < 0.0) ? ((mo > -0.5) ? ceil(pq) : floor(pq)) : ((mo > 0.0) ? ((mo >= 0.5) ? ceil(pq) : floor(pq)) : pq));

		return (pq);
	}
	double FPrmPQ()
	{
		double	pq = 0.0;
		double	mo = 0.0;

		pq = (double)F.PPrmPQ + PAdjPQ();
		mo = fmod(pq, 1.0);
		pq = ((mo < 0.0) ? ((mo > -0.5) ? ceil(pq) : floor(pq)) : ((mo > 0.0) ? ((mo >= 0.5) ? ceil(pq) : floor(pq)) : pq));

		return (pq);
	}
	double FOrgPQ()
	{
		double	pq = 0.0;

		if ((F.StatID == (BYTE)0x10) && (F.IsOrig == (BYTE)1))
			pq = pq + (double)F.POrgPQ;
		else if ((F.StatID == (BYTE)0x00) && (m_Orig == (BYTE)1))
			pq = pq + FPrmPQ();
		else
			pq = pq + (double)F.POrgPQ;

		return (pq);
	}
	double FRemPQ()
	{
		double	pq = 0.0;

		pq = FPrmPQ() - (double)F.PUsePQ;

		return (pq);
	}
	// Move
	//
	// - Sets PSrc PPrmPQ by -PAdjPQ to PDst +PAdjPQ
	//
	double PMaxPQ(size_t& PKNo)
	{
		// Called on PSrc w/ PDst to find Maximum PPrmPQ Possible
		// If we've PAdj'd to Dst, then this allows reduction (++PPrmPQ)
		double	pq	= 0;
		double	ca	= 0;
		double	mo	= 0;

		for (POSITION x = m_PAdjs.GetHeadPosition(); x != NULL; m_PAdjs.GetNext(x))
		{
			CCustPOrdMSetPSetPAdj&	pa	= m_PAdjs.GetAt(x);

			if (pa.m_PKNo == PKNo)
			{
				ca = (double)pa.PAdjPQ;
				break;
			}
		}

		pq = FPrmPQ() - (double)F.DScnPQ - (double)F.DShpPQ - ca;
		mo = fmod(pq, 1.0);
		pq = ((mo < 0.0) ? ((mo > -0.5) ? ceil(pq) : floor(pq)) : ((mo > 0.0) ? ((mo >= 0.5) ? ceil(pq) : floor(pq)) : pq));

		return (pq);
	}
	double PMinPQ()
	{
		double	pq	= 0;

		pq = (double)F.PUsePQ;

		return (pq);
	}
	int OkToMS()
	{
		if ((F.StatID == (BYTE)0x10) || ((m_DBOp & CCustPOrdMSetPSet::DB_INSERT) == CCustPOrdMSetPSet::DB_INSERT))
		{
			if (FRemPQ() > 0)
			{
				return (1);
			}
		}

		return (0);
	}
	int OkToMD()
	{
		return (1);
	}

	CCustPOrdMSetPSetPAdjs			m_PAdjs;
	size_t							m_PKNo;
	BYTE							m_Orig;
	DBOP							m_DBOp;
};


class CCustPOrdMSetPSetTraits : public CElementTraits< CCustPOrdMSetPSet >
{
public:
	static bool CompareElements(CCustPOrdMSetPSet& ele1, CCustPOrdMSetPSet& ele2)
	{
		return (SqlTinyIntTraits::CompareElements(ele1.F.PrmdIX, ele2.F.PrmdIX));
	}
	static int CompareElementsOrdered(CCustPOrdMSetPSet& ele1, CCustPOrdMSetPSet& ele2)
	{
		return (SqlTinyIntTraits::CompareElementsOrdered(ele1.F.PrmdIX, ele2.F.PrmdIX));
	}
};

class CCustPOrdMSetPSets : public CAtlList< CCustPOrdMSetPSet, CCustPOrdMSetPSetTraits >
{
public:
	CCustPOrdMSetPSets() : x_PNew((POSITION)-1)
	{
		m_PNew.F.PPrmPQ = (double)0.0;
	}
	CCustPOrdMSetPSets(const CCustPOrdMSetPSets& PSets) : x_PNew((POSITION)-1)
	{
		Copy(PSets);

		m_PNew = PSets.m_PNew;
	}
	void Free()
	{
		if (GetCount() > 0)
		{
			RemoveAll();
		}
	}
	void Copy(const CCustPOrdMSetPSets& PSets)
	{
		if (&PSets == this)
		{
			return;
		}
		
		Free();
		
		if (PSets.GetCount() > 0)
		{
			AddTailList(&PSets);
		}

		x_PNew = PSets.x_PNew;
		m_PNew = PSets.m_PNew;
	}
	const CCustPOrdMSetPSets& operator=(const CCustPOrdMSetPSets& PSets)
	{
		Copy(PSets);
		
		return (static_cast<const CCustPOrdMSetPSets&>(*this));
	}
	CCustPOrdMSetPSet& Get(POSITION pos)
	{
		return ((pos == x_PNew) ? m_PNew : GetAt(pos));
	}
	bool PKToDT(size_t& PKNo, SqlDateTime& ToDT)
	{
		for (POSITION x = GetHeadPosition(); x != NULL; GetNext(x))
		{
			CCustPOrdMSetPSet&	px = GetAt(x);

			if (px.m_PKNo == PKNo)
			{
				ToDT = px.F.PrmdDT;
				return (true);
			}
		}
		return (false);
	}
	POSITION DoPAdj(const SqlDateTime& PSrcDT, const SqlDateTime& PDstDT, const double& PAdjPQ)
	{
		POSITION				pa	= NULL;
		POSITION				ps	= NULL;
		POSITION				pd	= NULL;

		for (ps = GetHeadPosition(); ps != NULL; GetNext(ps))
		{
			if (GetAt(ps).F.PrmdDT == PSrcDT)
			{
				break;
			}
		}

		return (pa);
	}

	POSITION				x_PNew;
	CCustPOrdMSetPSet		m_PNew;
};

class CCustPOrdMSet : public CUSTPORDMSET
{
public:
	typedef enum tagDBOp {
		DB_NULLOP			= 0,
		DB_INSERT			= 1,
		DB_EXISTS			= 2,
		DB_UPDATE			= 4,
		DB_DELETE			= 8
	} DBOP, * LPDBOP;

	CCustPOrdMSet() : x_PSet(NULL), x_PSrc(NULL), x_PDst(NULL), m_XAct(0), m_DBOp(DB_EXISTS)
	{
		PAdjPQ = (double)0.0;
	}
	CCustPOrdMSet(const CUSTPORDMSET& MSet) : x_PSet(NULL), x_PSrc(NULL), x_PDst(NULL), m_XAct(0), x_ADst(NULL), x_ASrc(NULL), m_DBOp(DB_EXISTS)
	{
		CustID = MSet.CustID;
		MatlID = MSet.MatlID;
		PartID = MSet.PartID;
		XYdsPU = MSet.XYdsPU;
		PPerSQ = MSet.PPerSQ;
		PrceCM = MSet.PrceCM;
		PrceSA = MSet.PrceSA;
		PrceUM = MSet.PrceUM;
		POrdCT = MSet.POrdCT;
		POrdPQ = MSet.POrdPQ;
		POrdSQ = MSet.POrdSQ;
		PPrmPQ = MSet.PPrmPQ;
		PPrmSQ = MSet.PPrmSQ;
		DOrdCT = MSet.DOrdCT;
		DRelPQ = MSet.DRelPQ;
		DRelSQ = MSet.DRelSQ;
		F.CustPO = MSet.F.CustPO;
		F.UPrmCT = MSet.F.UPrmCT;
		F.PPrmPQ = MSet.F.PPrmPQ;
		F.PPrmSQ = MSet.F.PPrmSQ;
		F.PUsePQ = MSet.F.PUsePQ;
		F.PUseSQ = MSet.F.PUseSQ;
		F.UScnCT = MSet.F.UScnCT;
		F.DScnPQ = MSet.F.DScnPQ;
		F.DScnSQ = MSet.F.DScnSQ;
		F.UShpCT = MSet.F.UShpCT;
		F.DShpPQ = MSet.F.DShpPQ;
		F.DShpSQ = MSet.F.DShpSQ;
		F.PMinDT = MSet.F.PMaxDT;
		F.PMaxDT = MSet.F.PMaxDT;
		F.StatID = MSet.F.StatID;
		O.UPrmCT = MSet.O.UPrmCT;
		O.PPrmPQ = MSet.O.PPrmPQ;
		O.PPrmSQ = MSet.O.PPrmSQ;
		O.PUsePQ = MSet.O.PUsePQ;
		O.PUseSQ = MSet.O.PUseSQ;
		O.UScnCT = MSet.O.UScnCT;
		O.DScnPQ = MSet.O.DScnPQ;
		O.DScnSQ = MSet.O.DScnSQ;
		O.UShpCT = MSet.O.UShpCT;
		O.DShpPQ = MSet.O.DShpPQ;
		O.DShpSQ = MSet.O.DShpSQ;
		O.PMinDT = MSet.O.PMinDT;
		O.PMaxDT = MSet.O.PMaxDT;

		switch(MSet.F.StatID & (BYTE)0xFF)
		{
		case 0x10:
			m_DBOp = DB_EXISTS;
			break;
		case 0x00:
			m_DBOp = DB_NULLOP;
			break;
		}

		cPSet = MSet.cPSet;
		pPSet = MSet.pPSet;
		cALog = MSet.cALog;
		pALog = MSet.pALog;

		for (LONG i = 0; i < MSet.cPSet; i++)
		{
			m_PSets.AddTail(CCustPOrdMSetPSet((size_t)(i + 1), MSet.pPSet[i]));
		}

		PAdjPQ = (double)0.0;
	}
	~CCustPOrdMSet()
	{
		m_PSets.Free();
	}
	const CCustPOrdMSet& operator=(const CCustPOrdMSet& MSet)
	{
		CustID = MSet.CustID;
		MatlID = MSet.MatlID;
		PartID = MSet.PartID;
		XYdsPU = MSet.XYdsPU;
		PPerSQ = MSet.PPerSQ;
		PrceCM = MSet.PrceCM;
		PrceSA = MSet.PrceSA;
		PrceUM = MSet.PrceUM;
		POrdCT = MSet.POrdCT;
		POrdPQ = MSet.POrdPQ;
		POrdSQ = MSet.POrdSQ;
		PPrmPQ = MSet.PPrmPQ;
		PPrmSQ = MSet.PPrmSQ;
		DOrdCT = MSet.DOrdCT;
		DRelPQ = MSet.DRelPQ;
		DRelSQ = MSet.DRelSQ;
		F.CustPO = MSet.F.CustPO;
		F.UPrmCT = MSet.F.UPrmCT;
		F.PPrmPQ = MSet.F.PPrmPQ;
		F.PPrmSQ = MSet.F.PPrmSQ;
		F.PUsePQ = MSet.F.PUsePQ;
		F.PUseSQ = MSet.F.PUseSQ;
		F.UScnCT = MSet.F.UScnCT;
		F.DScnPQ = MSet.F.DScnPQ;
		F.DScnSQ = MSet.F.DScnSQ;
		F.UShpCT = MSet.F.UShpCT;
		F.DShpPQ = MSet.F.DShpPQ;
		F.DShpSQ = MSet.F.DShpSQ;
		F.PMinDT = MSet.F.PMaxDT;
		F.PMaxDT = MSet.F.PMaxDT;
		F.StatID = MSet.F.StatID;
		O.UPrmCT = MSet.O.UPrmCT;
		O.PPrmPQ = MSet.O.PPrmPQ;
		O.PPrmSQ = MSet.O.PPrmSQ;
		O.PUsePQ = MSet.O.PUsePQ;
		O.PUseSQ = MSet.O.PUseSQ;
		O.UScnCT = MSet.O.UScnCT;
		O.DScnPQ = MSet.O.DScnPQ;
		O.DScnSQ = MSet.O.DScnSQ;
		O.UShpCT = MSet.O.UShpCT;
		O.DShpPQ = MSet.O.DShpPQ;
		O.DShpSQ = MSet.O.DShpSQ;
		O.PMinDT = MSet.O.PMinDT;
		O.PMaxDT = MSet.O.PMaxDT;

		cPSet = MSet.cPSet;
		pPSet = MSet.pPSet;
		cALog = MSet.cALog;
		pALog = MSet.pALog;

		x_PSet = MSet.x_PSet;
		x_PSrc = MSet.x_PSrc;
		x_PDst = MSet.x_PDst;
		m_XAct = MSet.m_XAct;
		x_ADst = MSet.x_ADst;
		x_ASrc = MSet.x_ASrc;
		m_DBOp = MSet.m_DBOp;
		m_PSets = MSet.m_PSets;

		PAdjPQ = MSet.PAdjPQ;
	}
	LPCTSTR StylID()
	{
		LPMATL			pM			= NULL;

		if ((pM = MatlLRR(MatlID)) != NULL)
			return (pM->StylID());

		return ((LPCTSTR)MatlID);
	}
	int InXAct()
	{
		return (m_XAct);
	}
	int Enable(UINT id)
	{
		if (x_PDst == (POSITION)NULL)
			return (0);

		CCustPOrdMSetPSet&	pd = m_PSets.Get(x_PDst);

		switch (id)
		{
		case IDC_BTN_NEW:
			if ((m_XAct == 1) && (x_PDst == m_PSets.x_PNew))
			{
				return (1);
			}
			break;
		case IDC_BTN_UPD:
			if ((m_XAct == 1) && (x_PDst != m_PSets.x_PNew))
			{
				return(1);
			}
			break;
		case IDC_BTN_DEL:
			if (m_XAct == 0)
			{
				if ((pd.F.StatID == (BYTE)0x00) && ((pd.m_DBOp & CCustPOrdMSetPSet::DB_INSERT) == CCustPOrdMSetPSet::DB_INSERT))
				{
					return (1);
				}
			}
			if (m_XAct == 1)
			{
				return (1);
			}
			break;
		default:
			break;
		}

		return (0);
	}
	bool IsUsed()
	{
		return (((F.StatID == (BYTE)0x10) || ((m_DBOp & CCustPOrdMSet::DB_INSERT) == CCustPOrdMSet::DB_INSERT)) ? true : false);
	}
	BYTE IsOrig()
	{
		return (((F.StatID == (BYTE)0x00) && ((m_DBOp & CCustPOrdMSet::DB_INSERT) == CCustPOrdMSet::DB_INSERT)) ? (BYTE)1 : (BYTE)0);
	}
	int DoMove(CCustPOrdMSetPSet& PSrc, CCustPOrdMSetPSet& PDst, SqlNumeric<9, 2>& PAdjPQ)
	{
		SqlNumeric<9, 2>	PPosPQ;
		SqlNumeric<9, 2>	PNegPQ;

		m_XAct = 1;

		// Set/Add Dst (+)
		for (POSITION x = PDst.m_PAdjs.GetHeadPosition(); x != NULL; PDst.m_PAdjs.GetNext(x))
		{
			if (PDst.m_PAdjs.GetAt(x).m_PKNo == PSrc.m_PKNo)
			{
				x_ADst = x;
				PPosPQ = PAdjPQ;
				PDst.m_PAdjs.GetAt(x).DoMove(PPosPQ);
				break;
			}
		}
		if (PPosPQ == SqlNull)
		{
			PPosPQ = PAdjPQ;
			x_ADst = PDst.m_PAdjs.AddTail(CCustPOrdMSetPSetPAdj(PSrc.m_PKNo, PSrc.F.PrmdDT, PPosPQ));
		}
		// Set/Add Src (-)
		for (POSITION x = PSrc.m_PAdjs.GetHeadPosition(); x != NULL; PSrc.m_PAdjs.GetNext(x))
		{
			if (PSrc.m_PAdjs.GetAt(x).m_PKNo == PDst.m_PKNo)
			{
				x_ASrc = x;
				PNegPQ = ((double)-1.0 * (double)PAdjPQ);
				PSrc.m_PAdjs.GetAt(x).DoMove(PNegPQ);
				break;
			}
		}
		if (PNegPQ == SqlNull)
		{
			PNegPQ = ((double)-1.0 * (double)PAdjPQ);
			x_ASrc = PSrc.m_PAdjs.AddTail(CCustPOrdMSetPSetPAdj(PDst.m_PKNo, PDst.F.PrmdDT, PNegPQ));
		}

		return (1);
	}
	int UnMove(CCustPOrdMSetPSet& PSrc, CCustPOrdMSetPSet& PDst)
	{
		if (m_XAct == 0)
			return (0);

		m_XAct = 0;

		// Set/Add Dst (+)
		for (POSITION x = PDst.m_PAdjs.GetHeadPosition(); x != NULL; PDst.m_PAdjs.GetNext(x))
		{
			if (x == x_ADst)
			{
				PDst.m_PAdjs.RemoveAt(x_ADst);
				break;
			}
		}
		// Set/Add Src (-)
		for (POSITION x = PSrc.m_PAdjs.GetHeadPosition(); x != NULL; PSrc.m_PAdjs.GetNext(x))
		{
			if (x == x_ASrc)
			{
				PSrc.m_PAdjs.RemoveAt(x_ASrc);
				break;
			}
		}

		x_ADst = (POSITION)NULL;
		x_ASrc = (POSITION)NULL;

		return (1);
	}
	int DoEdit(CCustPOrdMSetPSet& PDst, SqlNumeric<9, 2>& PAdjPQ)
	{
		m_XAct = 1;

		// Set/Add Dst (+)
		for (POSITION x = PDst.m_PAdjs.GetHeadPosition(); x != NULL; PDst.m_PAdjs.GetNext(x))
		{
			if (PDst.m_PAdjs.GetAt(x).m_PKNo == PDst.m_PKNo)
			{
				x_ADst = x;
				PDst.m_PAdjs.GetAt(x).DoEdit(PAdjPQ);
				return (1);
			}
		}

		x_ADst = PDst.m_PAdjs.AddTail(CCustPOrdMSetPSetPAdj(PDst.m_PKNo, PDst.F.PrmdDT, PAdjPQ));

		return (1);
	}
	int UnEdit(CCustPOrdMSetPSet& PDst)
	{
		if (m_XAct == 0)
			return (0);

		m_XAct = 0;

		// Set/Add Dst (+)
		for (POSITION x = PDst.m_PAdjs.GetHeadPosition(); x != NULL; PDst.m_PAdjs.GetNext(x))
		{
			if (x == x_ADst)
			{
				PDst.m_PAdjs.RemoveAt(x_ADst);
				break;
			}
		}

		x_ADst = (POSITION)NULL;

		return (1);
	}
	POSITION FindPSet(CDateTimeCtrl& dt)
	{
		
		SYSTEMTIME	st;	memset(&st, 0, sizeof(SYSTEMTIME));
		DATE		vt	= 0;
		POSITION	xp	= NULL;

		if (dt.GetTime(&st) == GDT_VALID)
		{
			::SystemTimeToVariantTime(&st, &vt);
			vt = floor(vt);
			::VariantTimeToSystemTime(vt, &st);

			if (m_PSets.m_PNew.F.PrmdDT == st)
			{
				xp = m_PSets.x_PNew;
			}
			else
			{
				for (xp = m_PSets.GetHeadPosition(); xp != NULL; m_PSets.GetNext(xp))
				{
					CCustPOrdMSetPSet& ps = m_PSets.GetAt(xp);

					// Active
					if (((ps.F.StatID == (BYTE)0x00) && (ps.m_DBOp != CCustPOrdMSetPSet::DB_NULLOP))
					||	((ps.F.StatID == (BYTE)0x10) && (ps.m_DBOp != CCustPOrdMSetPSet::DB_DELETE)))
					{
						if (ps.F.PrmdDT == st)
						{
							break;
						}
					}
				}
			}
		}
		return (xp);
	}
	POSITION FindPSet(SYSTEMTIME& st)
	{
		
		DATE		vt	= 0;
		POSITION	xp	= NULL;

		if (1)
		{
			::SystemTimeToVariantTime(&st, &vt);
			vt = floor(vt);
			::VariantTimeToSystemTime(vt, &st);

			if (m_PSets.m_PNew.F.PrmdDT == st)
			{
				xp = m_PSets.x_PNew;
			}
			else
			{
				for (xp = m_PSets.GetHeadPosition(); xp != NULL; m_PSets.GetNext(xp))
				{
					CCustPOrdMSetPSet& ps = m_PSets.GetAt(xp);

					// Active
					if (((ps.F.StatID == (BYTE)0x00) && (ps.m_DBOp != CCustPOrdMSetPSet::DB_NULLOP))
					||	((ps.F.StatID == (BYTE)0x10) && (ps.m_DBOp != CCustPOrdMSetPSet::DB_DELETE)))
					{
						if (ps.F.PrmdDT == st)
						{
							break;
						}
					}
				}
			}
		}
		return (xp);
	}

	//
	// Conversion Notes
	// - When XQ -> CT, we always round up unit count using XYdsPU to get UQtyCT
	// - When CT -> XQ, we must calculate avg XYdsPU from DRelXQ / UQtyCT
	//
	// Conversion
	template<byte p, byte s>
	short UQtyCT(SqlNumeric<p, s>& DQtyPQ)
	{
		double	pq = (double)DQtyPQ;
		double	cf = (double)XYdsPU;
		short	ct = (short)ceil(pq / cf);

		return (ct);
	}
	short UQtyCT(double DQtyPQ)
	{
		double	pq = (double)DQtyPQ;
		double	cf = (double)XYdsPU;
		short	ct = (short)ceil(pq / cf);

		return (ct);
	}
	template<byte p, byte s>
	double DQtySQ(SqlNumeric<p, s>& DQtyPQ)
	{
		double	pq = (double)DQtyPQ;
		double	cf = (double)PPerSQ;
		double	sq = (pq / cf);

		return (sq);
	}
	double DQtySQ(double DQtyPQ)
	{
		double	pq = (double)DQtyPQ;
		double	cf = (double)PPerSQ;
		double	sq = (pq / cf);

		return (sq);
	}
	template<byte p, byte s>
	double DQtyPQ(SqlNumeric<p, s>& DQtySQ)
	{
		double	sq = (double)DQtySQ;
		double	cf = (double)PPerSQ;
		double	pq = (sq * cf);

		if ((pq - floor(pq)) >= 0.5)
			pq = ceil(pq);
		else
			pq = floor(pq);

		return (pq);
	}
	double DQtyPQ(double DQtySQ)
	{
		double	sq = (double)DQtySQ;
		double	cf = (double)PPerSQ;
		double	pq = (sq * cf);

		if ((pq - floor(pq)) >= 0.5)
			pq = ceil(pq);
		else
			pq = floor(pq);

		return (pq);
	}
	double DQtyPQ(SqlSmallInt& UQtyCT)
	{
		short	ct = (short)UQtyCT;
		double	cf = (double)XYdsPU; // MOrdPQ() / this->UQtyCT(MOrdPQ());
		double	pq = (ct * cf);

		return (pq);
	}
	double DQtyPQ(short UQtyCT)
	{
		short	ct = (short)UQtyCT;
		double	cf = (double)XYdsPU; // MOrdPQ() / this->UQtyCT(MOrdPQ());
		double	pq = (ct * cf);

		return (pq);
	}
	// Status
	double MOrdPQ()
	{
		//
		// Adjustments to POrd only resides in CCustPOrdMSetPSetPAdj where PSet.m_PKNo == PAdj.m_PKNo
		// 
		double	pq = (double)F.PPrmPQ;
		double	mo = 0.0;

		for (POSITION y = m_PSets.m_PNew.m_PAdjs.GetHeadPosition(); y != NULL; m_PSets.m_PNew.m_PAdjs.GetNext(y))
		{
			CCustPOrdMSetPSetPAdj&	pa = m_PSets.m_PNew.m_PAdjs.GetAt(y);

			if (pa.m_PKNo == m_PSets.m_PNew.m_PKNo)
			{
				pq = pq + (double)pa.PAdjPQ;
			}
		}

		for (POSITION x = m_PSets.GetHeadPosition(); x != NULL; m_PSets.GetNext(x))
		{
			CCustPOrdMSetPSet&	ps = m_PSets.Get(x);

			for (POSITION y = ps.m_PAdjs.GetHeadPosition(); y != NULL; ps.m_PAdjs.GetNext(y))
			{
				CCustPOrdMSetPSetPAdj&	pa = ps.m_PAdjs.GetAt(y);

				if (pa.m_PKNo == ps.m_PKNo)
				{
					pq = pq + (double)pa.PAdjPQ;
				}
			}
		}

		mo = fmod(pq, 1.0);
		pq = ((mo < 0.0) ? ((mo > -0.5) ? ceil(pq) : floor(pq)) : ((mo > 0.0) ? ((mo >= 0.5) ? ceil(pq) : floor(pq)) : pq));

		return (pq);
	}
	double MRemPQ()
	{
		double	pq = 0;

		// pq = pq + (MOrdPQ() + (double)O.PPrmPQ) - (double)F.PUsePQ + (double)F.DScnPQ - (double)O.PUsePQ + (double)O.DScnPQ;
		pq = pq + MOrdPQ() - (double)F.DScnPQ - (double)F.DShpPQ;
		// pq = pq - (double)DRelPQ;

		return (pq);
	}
	double MMinPQ()
	{
		double	pq = 0;

		pq = (double)F.PUsePQ;

		return (pq);
	}
	double MMaxPQ()
	{
		double	pq = 9999999.99;

		return (pq);
	}

	SqlNumeric<9, 2>				PAdjPQ;

	POSITION						x_PSet;
	POSITION						x_PSrc;
	POSITION						x_PDst;
	int								m_XAct;
	POSITION						x_ADst;
	POSITION						x_ASrc;
	DBOP							m_DBOp;
	CCustPOrdMSetPSets				m_PSets;
};


class CCustPOrdMSetTraits : public CElementTraits< CCustPOrdMSet >
{
public:
	static bool CompareElements(CCustPOrdMSet& ele1, CCustPOrdMSet& ele2)
	{
		return (SqlVarCharTraits<15>::CompareElements(ele1.MatlID, ele2.MatlID));
	}
	static int CompareElementsOrdered(CCustPOrdMSet& ele1, CCustPOrdMSet& ele2)
	{
		return (SqlVarCharTraits<15>::CompareElementsOrdered(ele1.MatlID, ele2.MatlID));
	}
};

class CCustPOrdMSets : public CAtlList< CCustPOrdMSet, CCustPOrdMSetTraits >
{
public:
	CCustPOrdMSets()
	{
	}
	CCustPOrdMSets(const CCustPOrdMSet& MSets)
	{
		Copy(MSets);
	}
	void Free()
	{
		if (GetCount() > 0)
		{
			RemoveAll();
		}
	}
	void Copy(const CCustPOrdMSets& MSets)
	{
		if (&MSets == this)
		{
			return;
		}

		Free();
		
		if (MSets.GetCount() > 0)
		{
			AddTailList(&MSets);
		}
	}
	const CCustPOrdMSets& operator=(const CCustPOrdMSets& MSets)
	{
		Copy(MSets);
		
		return (static_cast<CCustPOrdMSets&>(*this));
	}
};


// <Unused>
class CCustPOrdMatlXOrd : public CUSTPORDMATLXORD
{
public:
	typedef enum tagDBOp {
		DB_NULLOP			= 0,
		DB_INSERT			= 1,
		DB_EXISTS			= 2,
		DB_ADJQTY			= 4,
		DB_DELETE			= 8,
		DB_RELDDT			= 16,
		DB_SHPDDT			= 32,
		DB_PRMDDT			= 64
	} DBOP, * LPDBOP;
	
	CCustPOrdMatlXOrd() : m_DBOp(DB_NULLOP)
	{
		m_PKey = (double)0.0;
		m_QAdj = (double)0;
		m_RLAQ = (double)0;
		m_RRAQ = (double)0;
	}
	CCustPOrdMatlXOrd(const CUSTPORDMATLXORD& XOrd) : m_DBOp(DB_EXISTS)
	{
		CustID = XOrd.CustID;
		CustPO = XOrd.CustPO;
		MatlID = XOrd.MatlID;
		RQ.ReqdDT = XOrd.RQ.ReqdDT;
		RQ.COrdNo = XOrd.RQ.COrdNo;
		RQ.CReqPQ = XOrd.RQ.CReqPQ;
		RQ.CAlcPQ = XOrd.RQ.CAlcPQ;
		RQ.CAlcSQ = XOrd.RQ.CAlcSQ;
		RQ.NoteSZ = XOrd.RQ.NoteSZ;
		RQ.StatDT = XOrd.RQ.StatDT;
		RQ.StatID = XOrd.RQ.StatID;
		RL.ReldDT = XOrd.RL.ReldDT;
		RL.DOrdNo = XOrd.RL.DOrdNo;
		RL.URelCT = XOrd.RL.URelCT;
		RL.DRelPQ = XOrd.RL.DRelPQ;
		RL.DRelSQ = XOrd.RL.DRelSQ;
		RL.UScnCT = XOrd.RL.UScnCT;
		RL.DScnPQ = XOrd.RL.DScnPQ;
		RL.UShpCT = XOrd.RL.UShpCT;
		RL.DShpPQ = XOrd.RL.DShpPQ;
		DO.DOrdNo = XOrd.DO.DOrdNo;
		DO.URelCT = XOrd.DO.URelCT;
		DO.DRelPQ = XOrd.DO.DRelPQ;
		DO.DRelSQ = XOrd.DO.DRelSQ;
		DO.UScnCT = XOrd.DO.UScnCT;
		DO.DScnPQ = XOrd.DO.DScnPQ;
		DO.UShpCT = XOrd.DO.UShpCT;
		DO.DShpPQ = XOrd.DO.DShpPQ;
		DO.DShpDT = XOrd.DO.DShpDT;

		m_PKey = floor((double)RQ.ReqdDT) + (floor((double)RL.ReldDT) / 1000000.0);
		m_QAdj = (double)0;
		m_RLAQ = (double)0;
		m_RRAQ = (double)0;
	}
	~CCustPOrdMatlXOrd()
	{
	}

	const CCustPOrdMatlXOrd& operator=(const CCustPOrdMatlXOrd& XOrd)
	{
		CustID = XOrd.CustID;
		CustPO = XOrd.CustPO;
		MatlID = XOrd.MatlID;
		RQ.ReqdDT = XOrd.RQ.ReqdDT;
		RQ.COrdNo = XOrd.RQ.COrdNo;
		RQ.CReqPQ = XOrd.RQ.CReqPQ;
		RQ.CAlcPQ = XOrd.RQ.CAlcPQ;
		RQ.CAlcSQ = XOrd.RQ.CAlcSQ;
		RQ.NoteSZ = XOrd.RQ.NoteSZ;
		RQ.StatDT = XOrd.RQ.StatDT;
		RQ.StatID = XOrd.RQ.StatID;
		RL.ReldDT = XOrd.RL.ReldDT;
		RL.DOrdNo = XOrd.RL.DOrdNo;
		RL.URelCT = XOrd.RL.URelCT;
		RL.DRelPQ = XOrd.RL.DRelPQ;
		RL.DRelSQ = XOrd.RL.DRelSQ;
		RL.UScnCT = XOrd.RL.UScnCT;
		RL.DScnPQ = XOrd.RL.DScnPQ;
		RL.UShpCT = XOrd.RL.UShpCT;
		RL.DShpPQ = XOrd.RL.DShpPQ;
		DO.DOrdNo = XOrd.DO.DOrdNo;
		DO.URelCT = XOrd.DO.URelCT;
		DO.DRelPQ = XOrd.DO.DRelPQ;
		DO.DRelSQ = XOrd.DO.DRelSQ;
		DO.UScnCT = XOrd.DO.UScnCT;
		DO.DScnPQ = XOrd.DO.DScnPQ;
		DO.UShpCT = XOrd.DO.UShpCT;
		DO.DShpPQ = XOrd.DO.DShpPQ;
		DO.DShpDT = XOrd.DO.DShpDT;

		m_PKey = XOrd.m_PKey;
		m_QAdj = XOrd.m_QAdj;
		m_DBOp = XOrd.m_DBOp;
		m_RLAQ = XOrd.m_RLAQ;
		m_RRAQ = XOrd.m_RRAQ;

		return (static_cast<const CCustPOrdMatlXOrd&>(*this));
	}

	SqlNumeric<10, 2>& DRelAQ()
	{
		m_RLAQ = ((double)RL.DRelPQ + (double)m_QAdj);
		return (static_cast<SqlNumeric<10, 2>&>(m_RLAQ));
	}
	SqlNumeric<10, 2>& DRemAQ()
	{
		m_RRAQ = (double)DRelAQ();
		if (RL.DScnPQ != SqlNull)
			m_RRAQ -= (double)RL.DScnPQ;
		if (RL.DShpPQ != SqlNull)
			m_RRAQ -= (double)RL.DShpPQ;
		return (static_cast<SqlNumeric<10, 2>&>(m_RRAQ));
	}
	SqlNumeric<10, 2>& DMinAQ()
	{
		m_RRAQ = (double)0;
		if (RL.DScnPQ != SqlNull)
			m_RRAQ += (double)RL.DScnPQ;
		if (RL.DShpPQ != SqlNull)
			m_RRAQ += (double)RL.DShpPQ;
		return (static_cast<SqlNumeric<10, 2>&>(m_RRAQ));
	}
	SqlNumeric<12, 6>				m_PKey;
	SqlNumeric<9, 2>				m_QAdj;
	DBOP							m_DBOp;

private:
	SqlNumeric<10, 2>				m_RLAQ;
	SqlNumeric<10, 2>				m_RRAQ;
};

class CCustPOrdMatlXOrdTraits : public CElementTraits< CCustPOrdMatlXOrd >
{
public:
	static bool CompareElements(CCustPOrdMatlXOrd& ele1, CCustPOrdMatlXOrd& ele2)
	{
		return (SqlNumericTraits<12, 6>::CompareElements(ele1.m_PKey, ele2.m_PKey));
	}
	static int CompareElementsOrdered(CCustPOrdMatlXOrd& ele1, CCustPOrdMatlXOrd& ele2)
	{
		return (SqlNumericTraits<12, 6>::CompareElementsOrdered(ele1.m_PKey, ele2.m_PKey));
	}
};

class CCustPOrdMatlXOrds : public CAtlList< CCustPOrdMatlXOrd, CCustPOrdMatlXOrdTraits >
{
public:
	CCustPOrdMatlXOrds()
	{
	}
	CCustPOrdMatlXOrds(const CCustPOrdMatlXOrds& XOrds)
	{
		Copy(XOrds);
	}
	~CCustPOrdMatlXOrds()
	{
		Free();
	}
	SqlNumeric<10, 2>& CReqAQ(SqlDateTime& ReqdDT)
	{
		m_RQAQ = (double)0;
		
		for (POSITION p = GetHeadPosition(); p != NULL; GetNext(p))
		{
			if ((GetAt(p).m_DBOp & CCustPOrdMatlXOrd::DB_DELETE) != CCustPOrdMatlXOrd::DB_DELETE)
			{
				if (GetAt(p).RQ.ReqdDT == ReqdDT)
				{
					m_RQAQ += (double)GetAt(p).DRelAQ();
				}
			}
		}
		return (static_cast<SqlNumeric<10, 2>&>(m_RQAQ));
	}
	SqlNumeric<10, 2>& CReqAQ()
	{
		m_RQAQ = (double)0;
		
		for (POSITION p = GetHeadPosition(); p != NULL; GetNext(p))
		{
			if ((GetAt(p).m_DBOp & CCustPOrdMatlXOrd::DB_DELETE) != CCustPOrdMatlXOrd::DB_DELETE)
			{
				m_RQAQ += (double)GetAt(p).DRelAQ();
			}
		}
		return (static_cast<SqlNumeric<10, 2>&>(m_RQAQ));
	}
	SqlNumeric<10, 2>& DRelAQ()
	{
		m_RLAQ = (double)0;

		for (POSITION p = GetHeadPosition(); p != NULL; GetNext(p))
		{
			if ((GetAt(p).m_DBOp & CCustPOrdMatlXOrd::DB_DELETE) != CCustPOrdMatlXOrd::DB_DELETE)
			{
				m_RLAQ += (double)GetAt(p).DRelAQ();
			}
		}
		return (static_cast<SqlNumeric<10, 2>&>(m_RLAQ));
	}
	void Free()
	{
		if (GetCount() > 0)
		{
			RemoveAll();
		}
	}
	void Copy(const CCustPOrdMatlXOrds& XOrds)
	{
		if (&XOrds == this)
			return;
		Free();
		if (XOrds.GetCount() > 0)
		{
			AddTailList(&XOrds);
		}
	}
	const CCustPOrdMatlXOrds& operator=(const CCustPOrdMatlXOrds& XOrds)
	{
		Copy(XOrds);
		return (static_cast<const CCustPOrdMatlXOrds&>(*this));
	}

private:
	SqlNumeric<10, 2>				m_RQAQ;
	SqlNumeric<10, 2>				m_RLAQ;
};

class CCustPOrdMatl : public CUSTPORDMATL
{
public:
	typedef enum tagDBOp {
		DB_NULLOP			= 0,
		DB_INSERT			= 1,
		DB_EXISTS			= 2,
		DB_ADJQTY			= 4,
		DB_DELETE			= 8
	} DBOP, * LPDBOP;

	CCustPOrdMatl() : m_DBOp(DB_NULLOP)
	{
		m_QAdj = (double)0;
		m_POAQ = (double)0;
		m_PRAQ = (double)0;
	}
	CCustPOrdMatl(const CUSTPORDMATL& Matl) : m_DBOp(DB_EXISTS)
	{
		CustID = Matl.CustID;
		CustPO = Matl.CustPO;
		MatlID = Matl.MatlID;
		PartID = Matl.PartID;
		SAPrce = Matl.SAPrce;
		PMPrce = Matl.PMPrce;
		POrdPQ = Matl.POrdPQ;
		POrdSQ = Matl.POrdSQ;
		PrmdDT = Matl.PrmdDT;
		PM.CAlcPQ = Matl.PM.CAlcPQ;
		PM.DRelPQ = Matl.PM.DRelPQ;
		PM.DRemPQ = Matl.PM.DRemPQ;
		PM.DScnPQ = Matl.PM.DScnPQ;
		PM.DShpPQ = Matl.PM.DShpPQ;
		cXOrd = 0;
		pXOrd = NULL;

		m_QAdj = (double)0;
		m_POAQ = (double)0;
		m_PRAQ = (double)0;

		for (LONG i = 0; i < Matl.cXOrd; i++)
		{
			m_XOrds.AddTail(CCustPOrdMatlXOrd(Matl.pXOrd[i]));
		}
	}
	~CCustPOrdMatl()
	{
		m_XOrds.Free();
	}

	const CCustPOrdMatl& operator=(const CCustPOrdMatl& Matl)
	{
		CustID = Matl.CustID;
		CustPO = Matl.CustPO;
		MatlID = Matl.MatlID;
		PartID = Matl.PartID;
		SAPrce = Matl.SAPrce;
		PMPrce = Matl.PMPrce;
		POrdPQ = Matl.POrdPQ;
		POrdSQ = Matl.POrdSQ;
		PrmdDT = Matl.PrmdDT;
		PM.CAlcPQ = Matl.PM.CAlcPQ;
		PM.DRelPQ = Matl.PM.DRelPQ;
		PM.DRemPQ = Matl.PM.DRemPQ;
		PM.DScnPQ = Matl.PM.DScnPQ;
		PM.DShpPQ = Matl.PM.DShpPQ;
		cXOrd = 0;
		pXOrd = NULL;

		m_QAdj = Matl.m_QAdj;
		m_DBOp = Matl.m_DBOp;
		m_POAQ = Matl.m_POAQ;
		m_PRAQ = Matl.m_PRAQ;
		m_XOrds = Matl.m_XOrds;

		return (static_cast<const CCustPOrdMatl&>(*this));
	}

	SqlNumeric<9, 2>& POrdAQ()
	{
		m_POAQ = ((double)POrdPQ + (double)m_QAdj);
		return (static_cast<SqlNumeric<9, 2>&>(m_POAQ));
	}
	SqlNumeric<9, 2>& PRemAQ()
	{
		m_PRAQ = (double)POrdAQ();

		for (POSITION p = m_XOrds.GetHeadPosition(); p != NULL; m_XOrds.GetNext(p))
		{
			if ((m_XOrds.GetAt(p).m_DBOp & CCustPOrdMatlXOrd::DB_DELETE) != CCustPOrdMatlXOrd::DB_DELETE)
			{
				m_PRAQ -= (double)m_XOrds.GetAt(p).DRelAQ();
			}
			else if (m_XOrds.GetAt(p).RL.ReldDT != SqlNull)
			{
				m_PRAQ -= (double)m_XOrds.GetAt(p).DRelAQ();
			}
		}
		return (static_cast<SqlNumeric<9, 2>&>(m_PRAQ));
	}
	SqlNumeric<9, 2>& PAdjPQ()
	{
		return (static_cast<SqlNumeric<9, 2>&>(POrdAQ()));
	}
	SqlNumeric<9, 2>& PAdjSQ()
	{
		LPMATL	pM	= NULL;

		m_POAQ = SqlNull;

		if (MatlID != SqlNull)
		{
			if ((pM = MatlLRR(MatlID)) != NULL)
			{
				if ((pM->SQtyUID != SqlNull) && (pM->MPriPer != SqlNull) && (pM->MPriPer > (double)0))
				{
					m_POAQ = ((double)POrdAQ() / (double)pM->MPriPer);
				}
			}
		}
		return (static_cast<SqlNumeric<9, 2>&>(m_POAQ));
	}


	SqlNumeric<9, 2>				m_QAdj;		// Delta: m_edtPOrdPQ - POrdPQ
	DBOP							m_DBOp;
	CCustPOrdMatlXOrds				m_XOrds;

private:
	SqlNumeric<9, 2>				m_POAQ;
	SqlNumeric<9, 2>				m_PRAQ;
};

class CCustPOrdMatlTraits : public CElementTraits< CCustPOrdMatl >
{
public:
	static bool CompareElements(CCustPOrdMatl& ele1, CCustPOrdMatl& ele2)
	{
		return (SqlVarCharTraits<15>::CompareElements(ele1.MatlID, ele2.MatlID));
	}
	static int CompareElementsOrdered(CCustPOrdMatl& ele1, CCustPOrdMatl& ele2)
	{
		return (SqlVarCharTraits<15>::CompareElementsOrdered(ele1.MatlID, ele2.MatlID));
	}
};

class CCustPOrdMatls : public CAtlMap< SqlVarChar<15>, CCustPOrdMatl, SqlVarCharTraits<15>, CCustPOrdMatlTraits >
{
public:
	CCustPOrdMatls()
	{
		Init();
	}
	CCustPOrdMatls(const CCustPOrdMatls& Matls)
	{
		Init();
		Copy(Matls);
	}
	~CCustPOrdMatls()
	{
		Free();
	}
	void Init()
	{
		InitHashTable(10, false);
	}
	void Free()
	{
		if (GetCount() > 0)
		{
			RemoveAll();
		}
	}
	void Copy(const CCustPOrdMatls& Matls)
	{
		if (&Matls == this)
			return;
		Free();
		for (POSITION p = Matls.GetStartPosition(); p != NULL; Matls.GetNext(p))
		{
			SqlVarChar<15>		k = Matls.GetKeyAt(p);
			CCustPOrdMatl		v = Matls.GetValueAt(p);

			SetAt(k, CCustPOrdMatl(v));
		}
	}
	const CCustPOrdMatls& operator=(const CCustPOrdMatls& Matls)
	{
		Copy(Matls);
		return (static_cast<const CCustPOrdMatls&>(*this));
	}
};
// </Unused>

class CCustPOrd : public CUSTPORD
{
public:
	typedef enum tagDBOp {
		DB_NULLOP			= 0,
		DB_INSERT			= 1,
		DB_EXISTS			= 2,
		DB_UPDATE			= 4,
		DB_DELETE			= 8
	} DBOP, * LPDBOP;

	CCustPOrd() : m_DBOp(DB_NULLOP)
	{
	}
	CCustPOrd(const CUSTPORD& POrd) : m_DBOp(DB_EXISTS)
	{
		CustID = POrd.CustID;
		CustPO = POrd.CustPO;
		CrtdDT = POrd.CrtdDT;
		OpndDT = POrd.OpndDT;
		ClsdDT = POrd.ClsdDT;
		cMSet = POrd.cMSet;
		pMSet = POrd.pMSet;
		cMatl = 0;
		pMatl = NULL;

		m_PDst.Opened = false;
		m_DBOp = ((POrd.CustPO.Status == DBSTATUS_S_ISNULL) ? DB_INSERT : DB_EXISTS);

		for (LONG i = 0; i < POrd.cMSet; i++)
		{
			m_MSets.AddTail(CCustPOrdMSet(POrd.pMSet[i]));
		}
	}
	~CCustPOrd()
	{
		m_MSets.Free();
	}
	const CCustPOrd& operator=(const CCustPOrd& POrd)
	{
		CustID = POrd.CustID;
		CustPO = POrd.CustPO;
		CrtdDT = POrd.CrtdDT;
		OpndDT = POrd.OpndDT;
		ClsdDT = POrd.ClsdDT;
		cMSet = POrd.cMSet;
		pMSet = POrd.pMSet;
		cMatl = 0;
		pMatl = NULL;

		m_PDst.Opened = POrd.m_PDst.Opened;
		m_PDst.PrmdDT = POrd.m_PDst.PrmdDT;
		m_DBOp = POrd.m_DBOp;
		m_MSets = POrd.m_MSets;
	}

	struct tagPDst {
		bool						Opened;
		SqlDateTime					PrmdDT;
	}								m_PDst;

	DBOP							m_DBOp;
	CCustPOrdMSets					m_MSets;
};

class CCustPOrdDlg : public CDialog
{
	//
	// General UI Flow
	// - User checks materials from customer materials list that are PO. If not check, cannot select and/or focus
	// - Dialog starts out in Edit Mode, New and Transfer Modes are available when specific conditions exists based on promised date(s) selected
	// - Edit Mode
	//   - User selects one or more materials checked
	//   - CMPrce/SAPrce is a rim of materials list. Up/Down/Left/Right material navigation
	//   - PAdjXQ is a rim of promise dates list. Promise dats list is a child hub of materials list. Up/Down/Left/Right promise date, then material navigation
	// - New Mode
	//   - User selects one or more materials checked, but the one focused displays it's promise dates
	//   - User focuses on new promise date and selects a date, then new button enables. Clicking New Button re-selects all materials that can have that promise data added
	//   - User focuses on PAdjPQ and enters = quantity. Up/Down material navigation. 0 means no add. Save or Undo to return to edit mode
	// - Transfer mode
	//   - User selects one or more materials checked, but the one focused displays it's promise dates
	//   - User selects 2 promise dates (must follow entry into New Mode if want to transfer to new), then transfer button enables. Clicking Transfer Button re-selects all materials that match
	//   - User focuses on PAdjPQ and enters +/- or + quantity. Up/Down material navigation. 0 means no transfer. Save or Undo to return to edit mode


	DECLARE_DYNAMIC(CCustPOrdDlg)

public:
	CCustPOrdDlg(CWnd* pParent, NODEMENUCONSTANT Task, LPCUST pCust, LPCUSTPORD pPOrd);							// standard constructor
	CCustPOrdDlg(CWnd* pParent, NODEMENUCONSTANT Task, LPCUST pCust, LPCUSTPORD pPOrd, LPCUSTPORDMSET pMSet);	// schedule constructor

	virtual ~CCustPOrdDlg();

// Dialog Data
	enum { IDD = IDD_DLG_CUSTPORD };

	typedef enum tagXAct : BYTE
	{
		XA_NEDT			= 0x01,
		XA_NNEW			= 0x02,
		XA_NXFR			= 0x04
	}
	XACT, * LPXACT;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	NODEMENUCONSTANT				m_Task;
	CCustPOrd						m_POrd;
	LPCUST							p_Cust;
	LPCUSTPORD						p_POrd;
	LPCUSTMATL						p_CustMatl;
	LPMATL							p_Matl;
	LPCUSTPORDMSET					p_MSet;
	LPCUSTPORDMSETPSET				p_PSet;
	POSITION						x_MSet;
	POSITION						x_PSet;
	byte							x_Fcsd;
	byte							m_Col1;
	BYTE							m_XAct;
	CTime*							p_2Day;
	CTime*							p_ReqdMN;
	CTime*							p_ReqdMX;

	AFXCNTRLLIB::CPSEdit			m_edtCustID;
	AFXCNTRLLIB::CPSEdit			m_edtCustSZ;
	AFXCNTRLLIB::CPSEdit			m_edtCustPO;
	AFXCNTRLLIB::CPSDateTimeCtrl	m_dtpCrtdDT;
	AFXCNTRLLIB::CPSDateTimeCtrl	m_dtpOpndDT;
	AFXCNTRLLIB::CPSDateTimeCtrl	m_dtpClsdDT;
	AFXCNTRLLIB::CPSHubListCtrl		m_lvwMatl;
	AFXCNTRLLIB::CPSRimEdit			m_edtCMPrce;
	AFXCNTRLLIB::CPSRimEdit			m_edtSAPrce;
	AFXCNTRLLIB::CPSEdit			m_edtPOrdXQ;
	AFXCNTRLLIB::CPSEdit			m_edtXOrdXS;
	AFXCNTRLLIB::CPSEdit			m_edtXRemXS;
	CTabCtrl						m_tabPOrd;
	AFXCNTRLLIB::CPSHubListCtrl		m_lvwPSet;
	AFXCNTRLLIB::CPSRimEdit			m_edtPAdjXQ;
	AFXCNTRLLIB::CPSDateTimeCtrl	m_dtpPSrcDT;
	AFXCNTRLLIB::CPSDateTimeCtrl	m_dtpPDstDT;
	AFXCNTRLLIB::CPSEdit			m_edtXOrgXS;
	AFXCNTRLLIB::CPSEdit			m_edtXPrmXS;
	AFXCNTRLLIB::CPSEdit			m_edtXScnXS;
	AFXCNTRLLIB::CPSEdit			m_edtXShpXS;
	AFXCNTRLLIB::CPSListCtrl		m_lvwALog;
	AFXCNTRLLIB::CPSEdit			m_edtCmntSZ;
	
	void ShowMatlList(POSITION pos = NULL);
	void ShowPSetList(POSITION pos = NULL);
	void ShowALogList(LONG pos = -1);

	LRESULT VerifyMSetChkState(int iItem, UINT uOldState, UINT uNewState);
	LRESULT VerifyMSetSelState(int iItem, UINT uOldState, UINT uNewState);
	LRESULT VerifyPSetSelState(int iItem, UINT uOldState, UINT uNewState);
	int SelectMSetsForXAct(XACT xa);

	bool Ok2Edt();

	bool InXEdt();

	bool Ok2New();
	bool InXNew();

	bool Ok2Xfr();
	bool InXXfr();

	int MSetXActOK(CCustPOrdMSet& ms);
	int MSetDoXAct(CCustPOrdMSet& ms);
	void PAdjXQUpdate(LPCTSTR tz);

	void DoTest();

	virtual BOOL OnInitDialog();

protected:
	virtual void OnOK();

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnChangeCustPO();
	afx_msg void OnDateTimeChangeCrtdDT(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDateTimeChangeOpndDT(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDateTimeChangeClsdDT(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnItemChangingMatl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnItemChangedMatl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRimCtrlMoveMatl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnGetInfoTipMatl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnColumnClickMatl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSetFocusCMPrce();
	afx_msg void OnUpdateCMPrce();
	afx_msg void OnKillFocusCMPrce();
	afx_msg void OnSetFocusSAPrce();
	afx_msg void OnUpdateSAPrce();
	afx_msg void OnKillFocusSAPrce();
	afx_msg void OnSetFocusPOrdXQ();
	afx_msg void OnUpdatePOrdXQ();
	afx_msg void OnKillFocusPOrdXQ();
	afx_msg void OnClickPUOM();
	afx_msg void OnClickSUOM();
	afx_msg void OnClickUUOM();
	afx_msg void OnItemChangingPSet(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnItemChangedPSet(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRimCtrlMovePSet(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSetFocusPAdjXQ();
	afx_msg void OnUpdatePAdjXQ();
	afx_msg void OnKillFocusPAdjXQ();
	afx_msg void OnDateTimeDropDownPDstDT(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDateTimeChangePDstDT(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDateTimeCloseUpPDstDT(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDateTimeChangePSrcDT(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickNew();
	afx_msg void OnClickXfr();
	afx_msg void OnClickUndo();
	afx_msg void OnClickSave();
	afx_msg void OnSelChangePOrd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnItemChangingALog(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnItemChangedALog(NMHDR *pNMHDR, LRESULT *pResult);
};


class CCustPOrdInsertAcc
{
public:
	SqlInt					rtn;
	CCustPOrd				rec;

	BEGIN_PARAM_MAP(CCustPOrdInsertAcc)
		SET_PARAM_TYPE(DBPARAMIO_OUTPUT)
		COLUMN_ENTRY_EX(1, DBTYPE_I4, 4, 0, 0, rtn.Value, rtn.Length, rtn.Status)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY_EX(2, DBTYPE_STR, 5, 0, 0, rec.CustID.Value, rec.CustID.Length, rec.CustID.Status)
		COLUMN_ENTRY_EX(3, DBTYPE_STR, 16, 0, 0, rec.CustPO.Value, rec.CustPO.Length, rec.CustPO.Status)
		COLUMN_ENTRY_EX(4, DBTYPE_DBTIMESTAMP, 16, 0, 0, rec.CrtdDT.Value, rec.CrtdDT.Length, rec.CrtdDT.Status)
		COLUMN_ENTRY_EX(5, DBTYPE_DBTIMESTAMP, 16, 0, 0, rec.OpndDT.Value, rec.OpndDT.Length, rec.OpndDT.Status)
		COLUMN_ENTRY_EX(6, DBTYPE_DBTIMESTAMP, 16, 0, 0, rec.ClsdDT.Value, rec.ClsdDT.Length, rec.ClsdDT.Status)
	END_PARAM_MAP()

	DEFINE_COMMAND_EX(CCustPOrdInsertAcc, L"exec ? = aspCustPOrdInsert ?, ?, ?, ?, ?;");
};

class CCustPOrdInsert : public CCommand< CAccessor< CCustPOrdInsertAcc >, CNoRowset >
{
public:
	HRESULT Insert(CSession& dbs)
	{
		HRESULT hr = Open(dbs, NULL); 
		if (FAILED(hr))
		{
			MsgBoxOleDBError(hr);
		}
		return (hr); 
	}
};

class CCustPOrdUpdateAcc
{
public:
	SqlInt					rtn;
	CCustPOrd				rec;

	BEGIN_PARAM_MAP(CCustPOrdUpdateAcc)
		SET_PARAM_TYPE(DBPARAMIO_OUTPUT)
		COLUMN_ENTRY_EX(1, DBTYPE_I4, 4, 0, 0, rtn.Value, rtn.Length, rtn.Status)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY_EX(2, DBTYPE_STR, 5, 0, 0, rec.CustID.Value, rec.CustID.Length, rec.CustID.Status)
		COLUMN_ENTRY_EX(3, DBTYPE_STR, 16, 0, 0, rec.CustPO.Value, rec.CustPO.Length, rec.CustPO.Status)
		COLUMN_ENTRY_EX(4, DBTYPE_DBTIMESTAMP, 16, 0, 0, rec.CrtdDT.Value, rec.CrtdDT.Length, rec.CrtdDT.Status)
		COLUMN_ENTRY_EX(5, DBTYPE_DBTIMESTAMP, 16, 0, 0, rec.OpndDT.Value, rec.OpndDT.Length, rec.OpndDT.Status)
		COLUMN_ENTRY_EX(6, DBTYPE_DBTIMESTAMP, 16, 0, 0, rec.ClsdDT.Value, rec.ClsdDT.Length, rec.ClsdDT.Status)
	END_PARAM_MAP()

	DEFINE_COMMAND_EX(CCustPOrdUpdateAcc, L"exec ? = aspCustPOrdUpdate ?, ?, ?, ?, ?;");
};

class CCustPOrdUpdate : public CCommand< CAccessor< CCustPOrdUpdateAcc >, CNoRowset >
{
public:
	HRESULT Update(CSession& dbs)
	{
		HRESULT hr = Open(dbs, NULL); 
		if (FAILED(hr))
		{
			MsgBoxOleDBError(hr);
		}
		return (hr); 
	}
};

class CCustPOrdDeleteAcc
{
public:
	SqlInt					rtn;
	CCustPOrd				rec;

	BEGIN_PARAM_MAP(CCustPOrdDeleteAcc)
		SET_PARAM_TYPE(DBPARAMIO_OUTPUT)
		COLUMN_ENTRY_EX(1, DBTYPE_I4, 4, 0, 0, rtn.Value, rtn.Length, rtn.Status)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY_EX(2, DBTYPE_STR, 5, 0, 0, rec.CustID.Value, rec.CustID.Length, rec.CustID.Status)
		COLUMN_ENTRY_EX(3, DBTYPE_STR, 16, 0, 0, rec.CustPO.Value, rec.CustPO.Length, rec.CustPO.Status)
	END_PARAM_MAP()

	DEFINE_COMMAND_EX(CCustPOrdDeleteAcc, L"exec ? = aspCustPOrdDelete ?, ?;");
};

class CCustPOrdDelete : public CCommand< CAccessor< CCustPOrdDeleteAcc >, CNoRowset >
{
public:
	HRESULT Delete(CSession& dbs)
	{
		HRESULT hr = Open(dbs, NULL); 
		if (FAILED(hr))
		{
			MsgBoxOleDBError(hr);
		}
		return (hr); 
	}
};

class CCustPOrdMSetDoOptnAcc
{
public:
	SqlInt					rtn;
	CCustPOrdMSet			rec;
	
	struct tagPRM 
	{
		SqlInt				DBOptn;
		SqlTinyInt			IsOrig;
	}						prm;

	BEGIN_PARAM_MAP(CCustPOrdMSetDoOptnAcc)
		SET_PARAM_TYPE(DBPARAMIO_OUTPUT)
		COLUMN_ENTRY_EX(1, DBTYPE_I4, 4, 0, 0, rtn.Value, rtn.Length, rtn.Status)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY_EX(2, DBTYPE_STR, 5, 0, 0, rec.CustID.Value, rec.CustID.Length, rec.CustID.Status)
		COLUMN_ENTRY_EX(3, DBTYPE_STR, 16, 0, 0, rec.F.CustPO.Value, rec.F.CustPO.Length, rec.F.CustPO.Status)
		COLUMN_ENTRY_EX(4, DBTYPE_STR, 16, 0, 0, rec.MatlID.Value, rec.MatlID.Length, rec.MatlID.Status)
		COLUMN_ENTRY_EX(5, DBTYPE_I4, 4, 0, 0, prm.DBOptn.Value, prm.DBOptn.Length, prm.DBOptn.Status)
		COLUMN_ENTRY_EX(6, DBTYPE_NUMERIC, 19, 6, 3, rec.PrceSA.Value, rec.PrceSA.Length, rec.PrceSA.Status)
		COLUMN_ENTRY_EX(7, DBTYPE_NUMERIC, 19, 6, 3, rec.PrceCM.Value, rec.PrceCM.Length, rec.PrceCM.Status)
		SET_PARAM_TYPE(DBPARAMIO_INPUT | DBPARAMIO_OUTPUT)
		COLUMN_ENTRY_EX(8, DBTYPE_UI1, 1, 0, 0, prm.IsOrig.Value, prm.IsOrig.Length, prm.IsOrig.Status)
	END_PARAM_MAP()

	DEFINE_COMMAND_EX(CCustPOrdMSetDoOptnAcc, L"exec ? = aspCustPOrdMSetDoOptn ?, ?, ?, ?, ?, ?, ? OUT;");
};

class CCustPOrdMSetDoOptn : public CCommand< CAccessor< CCustPOrdMSetDoOptnAcc >, CNoRowset >
{
public:
	HRESULT DoOptn(CSession& dbs)
	{
		HRESULT hr = Open(dbs, NULL); 
		if (FAILED(hr))
		{
			MsgBoxOleDBError(hr);
		}
		return (hr); 
	}
};

class CCustPOrdMSetPSetDoOptnAcc
{
public:
	SqlInt					rtn;
	CCustPOrdMSetPSet		rec;
	
	struct tagPRM 
	{
		SqlInt				DBOptn;
		SqlTinyInt			IsOrig;
		SqlVarChar<30>		UserID;
		SqlVarChar<30>		WStnID;
	}						prm;

	BEGIN_PARAM_MAP(CCustPOrdMSetPSetDoOptnAcc)
		SET_PARAM_TYPE(DBPARAMIO_OUTPUT)
		COLUMN_ENTRY_EX(1, DBTYPE_I4, 4, 0, 0, rtn.Value, rtn.Length, rtn.Status)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY_EX(2, DBTYPE_STR, 5, 0, 0, rec.CustID.Value, rec.CustID.Length, rec.CustID.Status)
		COLUMN_ENTRY_EX(3, DBTYPE_STR, 16, 0, 0, rec.F.CustPO.Value, rec.F.CustPO.Length, rec.F.CustPO.Status)
		COLUMN_ENTRY_EX(4, DBTYPE_STR, 16, 0, 0, rec.MatlID.Value, rec.MatlID.Length, rec.MatlID.Status)
		COLUMN_ENTRY_EX(5, DBTYPE_DBTIMESTAMP, 16, 0, 0, rec.F.PrmdDT.Value, rec.F.PrmdDT.Length, rec.F.PrmdDT.Status)
		COLUMN_ENTRY_EX(6, DBTYPE_I4, 4, 0, 0, prm.DBOptn.Value, prm.DBOptn.Length, prm.DBOptn.Status)
		COLUMN_ENTRY_EX(7, DBTYPE_UI1, 1, 0, 0, prm.IsOrig.Value, prm.IsOrig.Length, prm.IsOrig.Status)
		COLUMN_ENTRY_EX(8, DBTYPE_STR, 31, 0, 0, prm.UserID.Value, prm.UserID.Length, prm.UserID.Status)
		COLUMN_ENTRY_EX(9, DBTYPE_STR, 31, 0, 0, prm.WStnID.Value, prm.WStnID.Length, prm.WStnID.Status)
	END_PARAM_MAP()

	DEFINE_COMMAND_EX(CCustPOrdMSetPSetDoOptnAcc, L"exec ? = aspCustPOrdMSetPSetDoOptn ?, ?, ?, ?, ?, ?, ?, ?;");
};

class CCustPOrdMSetPSetDoOptn : public CCommand< CAccessor< CCustPOrdMSetPSetDoOptnAcc >, CNoRowset >
{
public:
	HRESULT DoOptn(CSession& dbs)
	{
		HRESULT hr = Open(dbs, NULL); 
		if (FAILED(hr))
		{
			MsgBoxOleDBError(hr);
		}
		return (hr); 
	}
};

class CCustPOrdMSetPSetDoPAdjAcc
{
public:
	SqlInt					rtn;
	CCustPOrdMSetPSetPAdj	rec;
	
	struct tagPRM 
	{
		SqlChar<4>			CustID;
		SqlVarChar<15>		CustPO;
		SqlVarChar<15>		MatlID;
		SqlInt				DBOptn;
		SqlTinyInt			IsOrig;
		SqlDateTime			PDstDT;
		SqlDateTime			PSrcDT;
		SqlChar<2>			ALogID;
		SqlDateTime			ALogDT;
		SqlVarChar<30>		UserID;
		SqlVarChar<30>		WStnID;
	}						prm;

	BEGIN_PARAM_MAP(CCustPOrdMSetPSetDoPAdjAcc)
		SET_PARAM_TYPE(DBPARAMIO_OUTPUT)
		COLUMN_ENTRY_EX(1, DBTYPE_I4, 4, 0, 0, rtn.Value, rtn.Length, rtn.Status)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY_EX(2, DBTYPE_STR, 5, 0, 0, prm.CustID.Value, prm.CustID.Length, prm.CustID.Status)
		COLUMN_ENTRY_EX(3, DBTYPE_STR, 16, 0, 0, prm.CustPO.Value, prm.CustPO.Length, prm.CustPO.Status)
		COLUMN_ENTRY_EX(4, DBTYPE_STR, 16, 0, 0, prm.MatlID.Value, prm.MatlID.Length, prm.MatlID.Status)
		COLUMN_ENTRY_EX(5, DBTYPE_I4, 4, 0, 0, prm.DBOptn.Value, prm.DBOptn.Length, prm.DBOptn.Status)
		COLUMN_ENTRY_EX(6, DBTYPE_UI1, 1, 0, 0, prm.IsOrig.Value, prm.IsOrig.Length, prm.IsOrig.Status)
		COLUMN_ENTRY_EX(7, DBTYPE_DBTIMESTAMP, 16, 0, 0, prm.PDstDT.Value, prm.PDstDT.Length, prm.PDstDT.Status)
		COLUMN_ENTRY_EX(8, DBTYPE_DBTIMESTAMP, 16, 0, 0, prm.PSrcDT.Value, prm.PSrcDT.Length, prm.PSrcDT.Status)
		COLUMN_ENTRY_EX(9, DBTYPE_NUMERIC, 19, 9, 2, rec.PAdjPQ.Value, rec.PAdjPQ.Length, rec.PAdjPQ.Status)
		COLUMN_ENTRY_EX(10, DBTYPE_STR, 4, 0, 0, prm.ALogID.Value, prm.ALogID.Length, prm.ALogID.Status)
		COLUMN_ENTRY_EX(11, DBTYPE_DBTIMESTAMP, 16, 0, 0, prm.ALogDT.Value, prm.ALogDT.Length, prm.ALogDT.Status)
		COLUMN_ENTRY_EX(12, DBTYPE_STR, 31, 0, 0, prm.UserID.Value, prm.UserID.Length, prm.UserID.Status)
		COLUMN_ENTRY_EX(13, DBTYPE_STR, 31, 0, 0, prm.WStnID.Value, prm.WStnID.Length, prm.WStnID.Status)
		COLUMN_ENTRY_EX(14, DBTYPE_STR, 256, 0, 0, rec.CmntSZ.Value, rec.CmntSZ.Length, rec.CmntSZ.Status)
	END_PARAM_MAP()

	DEFINE_COMMAND_EX(CCustPOrdMSetPSetDoPAdjAcc, L"exec ? = aspCustPOrdMSetPSetDoPAdj ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?;");
};

class CCustPOrdMSetPSetDoPAdj : public CCommand< CAccessor< CCustPOrdMSetPSetDoPAdjAcc >, CNoRowset >
{
public:
	HRESULT DoPAdj(CSession& dbs)
	{
		HRESULT hr = Open(dbs, NULL); 
		if (FAILED(hr))
		{
			MsgBoxOleDBError(hr);
		}
		return (hr); 
	}
};
