//------------------------------------------------------------------------------
// <copyright company="Microsoft Corporation">
//      Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;

namespace SQLConfigurator
{
	public interface IDataConnectionConfiguration
	{
		string GetSelectedSource();
		void SaveSelectedSource(string provider);

		string GetSelectedProvider();
		void SaveSelectedProvider(string provider);
	}
}
