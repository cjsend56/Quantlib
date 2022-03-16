import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

usdkrw = pd.read_csv('./CORR.csv')

usdkrw.corr()

plt.rcParams['font.family'] = "Malgun Gothic"
plt.figure(figsize=(14,8))
plt.title('자산별 Correlation', size=20)
plt.xticks(rotation=45)

sns.heatmap(usdkrw.corr(), annot = True)

plt.show()